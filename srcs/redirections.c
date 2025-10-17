#include "../includes/minishell.h"

static char	get_direction(t_node_type type)
{
	if (type == NODE_REDIR_IN)
		return ('I');
	else if (type == NODE_REDIR_HERE_DOC)
		return ('H');
	return ('O');
}

static int	redirect_input(char *filename, int *info_about_streams, char type)
{
	int	fd;
	int	stream_overwritten;

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

static int	redirect_output(t_tree_node *node, char *filename, 
	int *info_about_streams)
{
	int	fd;
	int	stream_overwritten;

	if (!check_folder(filename))
		return (-1);
	fd = 0;
	if (node->type == NODE_REDIR_OUT)
		fd = open_file(filename, O_RDWR | O_CREAT | O_TRUNC);
	else if (node->type == NODE_REDIR_OUT_APPEND)
		fd = open_file(filename, O_RDWR | O_CREAT | O_APPEND);
	if (fd == -1)
		return (-1);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'O');
	if (!stream_overwritten)
		overwrite_stream('O', info_about_streams, fd);
	return (fd);
}

int	execute_redirection(t_tree_node *node, t_shell *shell, int streams)
{
	int		status;
	char	direction;
	char	*filename;
	int		result;

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
