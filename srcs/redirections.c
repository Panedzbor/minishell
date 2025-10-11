#include "../includes/minishell.h"

static char get_direction(t_node_type type)
{
	if (type == NODE_REDIRECT_IN)
		return ('I');
	else if (type == NODE_REDIRECT_HERE_DOC)
		return ('H');
	return ('O');
}

static void redirect_input(char *filename, int *info_about_streams, char type)
{
	int fd;
	int stream_overwritten;

	fd = 0;
	if (type == 'I')
		fd = open_file(filename, O_RDONLY);
	else if (type == 'H')
		fd = open_file(filename, O_RDWR | O_CREAT);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'I');
	if (!stream_overwritten)
		overwrite_stream('I', info_about_streams, fd);
	close_file(fd);
}

static void redirect_output(t_tree_node *node, char *filename, int *info_about_streams)
{
	int fd;
	int stream_overwritten;

	fd = 0;
	if (node->type == NODE_REDIRECT_OUT)
		fd = open_file(filename, O_RDWR | O_CREAT | O_TRUNC);
	else if(node->type == NODE_REDIRECT_OUT_APPEND)
		fd = open_file(filename, O_RDWR | O_CREAT | O_APPEND);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'O');
	if (!stream_overwritten)
		overwrite_stream('O', info_about_streams, fd);
	close_file(fd);
}

//static char *process_filename_node(t_tree_node *node)
//{
//	char *filename;

//	filename = node->argv[0];
//	return (filename);
//}

//static int count_args(char *args)
//{
//	int i;

//	i = 0;
//	while (args[i])
//		i++;
//	return (i);
//}

//static void move_args(t_tree_node *node)
//{
//	int i;
//	int len;

//	len = count_args(node->right->argv);
//	i = 1;
//	while (node->right->argv[i])
//	{

//		i++;
//	}
//}

int execute_redirection(t_tree_node *node, t_shell *shell, int streams)
{
	int status;
	char direction;
	char *filename;

	filename = node->right->argv[0];
	direction = get_direction(node->type);
	if (direction == 'I')
		redirect_input(filename, &streams, 'I');
	else if (direction == 'H')
		redirect_input(filename, &streams, 'H');
	else if (direction == 'O')
		redirect_output(node, filename, &streams);
	//move_args(node);
	status = execute_command_line(node->left, shell, 0, streams);
	if (direction == 'H')
		unlink(filename);
	return (status);
}
