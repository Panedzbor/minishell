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
	
	if (node->type == NODE_REDIRECT_OUT)
		fd = open_file(filename, O_RDWR | O_CREAT | O_TRUNC);
	else if(node->type == NODE_REDIRECT_OUT_APPEND)
		fd = open_file(filename, O_RDWR | O_CREAT | O_APPEND);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'O');
	if (!stream_overwritten)
		overwrite_stream('O', info_about_streams, fd);
	close_file(fd);
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

// static void reset_heredoc_file(char *filename)
// {
// 	int fd;

// 	fd = open(filename, O_TRUNC);
// 	close(fd);
// 	unlink(filename);
// }

int execute_redirection(t_tree_node *node, t_shell *shell, int streams)
{
	int status;
	char direction;
	char *filename;
	//char *heredoc_file;

	filename = process_filename_node(node->right);
	direction = get_direction(node->type);
	if (direction == 'I')
		redirect_input(filename, &streams, 'I');
	else if (direction == 'H')
		redirect_input(filename, &streams, 'H');
	else if (direction == 'O')
		redirect_output(node, filename, &streams);
	// else if (direction == 'H')
	// {
	// 	heredoc_file = run_here_doc(filename, shell);
	// 	redirect_input(heredoc_file, &streams);
	// }
	status = execute_command_line(node->left, shell, 0/*?*/, streams);
	if (direction == 'H')
		unlink(filename);
	return (status);
}
