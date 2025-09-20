#include "../includes/minishell.h"

static int validate_command(t_tree_node *node, t_shell *shell)
{
	int status;
	char **cmd;


	cmd = node->argv;
	if (!ft_strncmp(cmd[0], "echo", 5))
		status = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		status = cd(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		status = pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		status = export(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		status = unset(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "env", 4))
		status = env(shell->envp);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		status = ft_printf("%s: found\n", cmd[0]);
	else
		status = call_external_command(cmd, shell);
	return (status);
}

static int execute_logic_operator(t_tree_node *node, t_shell *shell, int sub_pipe)
{
	int status;

	status = execute_command_line(node->left, shell, sub_pipe);
	if (status == 0 && node->type == NODE_AND)
		status = execute_command_line(node->right, shell, sub_pipe);
	else if (status != 0 && node->type == NODE_OR)
		status = execute_command_line(node->right, shell, sub_pipe);
	return (status);
}

/* static int assign_variable(t_tree_node *node, t_shell *shell)
{
	int i;

	i = 0;
	while (node->argv[i])
	{
		set_var(node->argv[i], &shell->local_vars);
		i++;
	}
	return (0);
} */

static int get_info_about_stream(int info_about_streams, char stream)
{
	if (stream == 'I')
		return (info_about_streams >> 1);
	else if (stream == 'O')
		return (info_about_streams & 1);
}


int open_file(char *filename, int flags)
{
	int fd;

	fd = open(filename, flags);
	if (fd == -1)
	{
		perror("error on opening the file\n");
		return (-1);// enter error handler here
	}
	return (fd);
}

static void overwrite_stream(char stream, int *info, int new_fd)
{
	if (stream == 'I')
	{
		dup2(new_fd, STDIN_FILENO);
		*info += 2;
	}
	else
	{
		dup2(new_fd, STDIN_FILENO);
		*info += 1;
	}
}

static char get_direction(t_node_type type)
{
	if (type == NODE_REDIRECT_IN || type == NODE_REDIRECT_IN_MANUAL)
		return ('I');
	return ('O');
}

void redirect_input(t_tree_node *node, char *filename, int *info_about_streams)
{
	int stream_overwritten;
	int fd;
	
	fd = open_file(filename, O_RDONLY);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'I');
	if (!stream_overwritten)
		overwrite_stream('I', info_about_streams, fd);
}

void redirect_output(t_tree_node *node, char *filename, int *info_about_streams)
{
	int stream_overwritten;
	int fd;
	
	if (node->type == NODE_REDIRECT_OUT)
		fd = open_file(filename, O_WRONLY | O_CREAT | O_TRUNC);
	else if(node->type == NODE_REDIRECT_OUT_APPEND)
		fd = open_file(filename, O_WRONLY | O_CREAT | O_APPEND);
	stream_overwritten = get_info_about_stream(*info_about_streams, 'O');
	if (!stream_overwritten)
		overwrite_stream('O', info_about_streams, fd);
}

static int execute_redirection(t_tree_node *node, t_shell *shell, int *streams)
{
	int status;
	char direction;
	char *filename;

	filename = execute_command_line(node->right, shell, 0);//TODO
	direction = get_direction(node->type);
	if (direction == 'I')
		redirect_input(node, filename, streams);
	else if (direction == 'O')
		redirect_output(node, filename, streams);
	status = execute_command_line(node->left, shell, 0);
	return (status);
}

int execute_command_line(t_tree_node *node, t_shell *shell, int sub_pipe)
{
    int status;

	status = 0;
	if (node->type == NODE_COMMAND)
        status = validate_command(node, shell);
    else if (node->type == NODE_PIPE)
        status = execute_pipe(node, shell, sub_pipe);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		status = execute_logic_operator(node, shell, sub_pipe);
	else if (node->type == NODE_REDIRECT_IN || node->type == NODE_REDIRECT_IN_MANUAL
			|| node->type == NODE_REDIRECT_OUT || node->type == NODE_REDIRECT_OUT_APPEND)
		status = execute_redirection(node, shell, &fd_flags_encoded);
	else if (node->type == NODE_FILENAME)
	{

	}
	return (status);
}
