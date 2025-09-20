#include "../includes/minishell.h"

static char get_direction(t_node_type type)
{
	if (type == NODE_REDIRECT_IN)
		return ('I');
	else if (type == NODE_REDIRECT_HERE_DOC)
		return ('H');
	return ('O');
}

static void redirect_input(/* t_tree_node *node,  */char *filename, int *info_about_streams)
{
	int fd;
	int stream_overwritten;
	
	fd = open_file(filename, O_RDONLY);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'I');
	if (!stream_overwritten)
		overwrite_stream('I', info_about_streams, fd);
}

static void redirect_output(t_tree_node *node, char *filename, int *info_about_streams)
{
	int fd;
	int stream_overwritten;
	
	if (node->type == NODE_REDIRECT_OUT)
		fd = open_file(filename, O_RDWR | O_CREAT | O_TRUNC);
	else if(node->type == NODE_REDIRECT_OUT_APPEND)
		fd = open_file(filename, O_RDWR | O_CREAT | O_APPEND);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'O');
	if (!stream_overwritten)
		overwrite_stream('O', info_about_streams, fd);
}

static char *process_filename_node(t_tree_node *node)
{
	char *filename;
	
	// Step 1: go through expansions
	
	// Step 2:
	// if no expansions:
	filename = node->argv[0];
	return (filename);
}

int same_string(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) == ft_strlen(str2) 
			&& !ft_strncmp(str1, str2, ft_strlen(str1)))
			return (1);
	return (0);
}

static void run_here_doc(t_tree_node *node, int *streams)
{
	char *stop_word;
	char *input;
	char *new_line;

	new_line = NULL;
	input = NULL;
	stop_word = node->right->argv[0];
	while (!same_string(new_line, stop_word))
	{
		input = join_new_line(new_line);
		new_line = readline("");// ? - will it print additional lines?
	}
	save_input_to_file(input);
	//if (input)
	free(input);
}

int execute_redirection(t_tree_node *node, t_shell *shell, int streams)
{
	int status;
	char direction;
	char *filename;

	filename = process_filename_node(node->right);
	direction = get_direction(node->type);
	if (direction == 'I')
		redirect_input(/* node,  */filename, &streams);
	else if (direction == 'O')
		redirect_output(node, filename, &streams);
	else if (direction == 'H')
	{
		run_here_doc(node, &streams);
		redirect_input(heredoc_file, &streams);
	}
	status = execute_command_line(node->left, shell, 0/*?*/, streams);
	return (status);
}