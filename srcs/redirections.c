#include "../includes/minishell.h"

static char get_direction(t_node_type type)
{
	if (type == NODE_REDIRECT_IN)
		return ('I');
	else if (type == NODE_REDIRECT_HERE_DOC)
		return ('H');
	return ('O');
}

static int check_file(char *filename)
{
	struct stat info;
	
	if (stat(filename, &info) == -1)
	{
		perror(" ");
		return (0);
	}
	return (1);
}

static int redirect_input(char *filename, int *info_about_streams, char type)
{
	int fd;
	int stream_overwritten;

	if (!check_file(filename))
		return (-1);
	fd = 0;
	if (type == 'I')
		fd = open_file(filename, O_RDONLY);
	else if (type == 'H')
		fd = open_file(filename, O_RDWR | O_CREAT);
	if (fd == -1)
		return (-1);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'I');
	if (!stream_overwritten)
		overwrite_stream('I', info_about_streams, fd);
	return (fd);
}

static int check_folder(char *filename)
{
	char *folder_name;
	int i;

	if (!ft_strchr(filename, '/'))
		return (1);
	i = 0;
	while (ft_strchr(filename + i, '/'))
		i++;
	folder_name = ft_substr(filename, 0, i);
	if (!folder_name)
		return (0);
	if (access(folder_name, F_OK) == -1)
	{
		free(folder_name);
		perror(" ");
		return (0);
	}
	free(folder_name);
	return (1);
}

static int redirect_output(t_tree_node *node, char *filename, int *info_about_streams)
{
	int fd;
	int stream_overwritten;

	if (!check_folder(filename))
		return (-1);
	fd = 0;
	if (node->type == NODE_REDIRECT_OUT)
		fd = open_file(filename, O_RDWR | O_CREAT | O_TRUNC);
	else if(node->type == NODE_REDIRECT_OUT_APPEND)
		fd = open_file(filename, O_RDWR | O_CREAT | O_APPEND);
	if (fd == -1)
		return (-1);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'O');
	if (!stream_overwritten)
		overwrite_stream('O', info_about_streams, fd);
	return (fd);
}

//static char *process_filename_node(t_tree_node *node)
//{
//	char *filename;

//	filename = node->argv[0];
//	return (filename);
//}

/* static int count_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
} */

static char **alloc_arg_mem(int size)
{
	char **temp;

	temp = (char **)ft_calloc(size + 1, sizeof(char *));
    if (!check_alloc(temp))
		return (NULL);
	return (temp);
}

static void ft_copy_arr(char **src, int src_strt, char **dest, int dest_strt)
{
	int s;
	int d;

	s = src_strt;
	d = dest_strt;
	while (src[s])
	{
		dest[d] = src[s];
		s++;
		d++;
	}
}

/*char **dupl_arr(char **arr, int len)
{
	int i;

	i = 0;

}*/

static int move_args(t_tree_node *node)
{
	int rlen;
	int llen;
	char **temp;
	char **dupl;

	rlen = ft_arr_el_count((void **)node->right->argv + 1);
	if (!rlen)
		return (1);
	llen = ft_arr_el_count((void **)node->left->argv);
	temp = alloc_arg_mem(llen + rlen);
	if (!temp)
		return (0);
	ft_copy_arr(node->left->argv, 0, temp, 0);
	dupl = ft_charrdup(node->right->argv + 1);
	ft_copy_arr(dupl, 0, temp, llen);
	free(dupl);
	temp[llen + rlen] = NULL;
	free(node->left->argv);
	node->left->argv = temp;
	return (1);
}

int execute_redirection(t_tree_node *node, t_shell *shell, int streams)
{
	int status;
	char direction;
	char *filename;
	int result;

	remove_quotes_from_argv(node->right->argv);
	filename = node->right->argv[0];
	direction = get_direction(node->type);
	result = 0;
	if (direction == 'I')
		result = redirect_input(filename, &streams, 'I');
	else if (direction == 'H')
		result = redirect_input(filename, &streams, 'H');
	else if (direction == 'O')
		result = redirect_output(node, filename, &streams);
	if (result == -1)
		return (1);
	if (!move_args(node))
		return (13);
	status = execute_command_line(node->left, shell, 0, streams);
	reset_streams(*shell);
	close(result);
	if (direction == 'H')
		unlink(filename);
	return (status);
}
