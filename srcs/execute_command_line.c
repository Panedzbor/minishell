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

static void extract_states_of_fd(int states_of_fd, int *input_state, int *output_state)
{
	*input_state = states_of_fd >> 1;
	*output_state = states_of_fd & 1;
}

static int stream_is_overwritten(t_tree_node *node, int input, int output)
{
	if (node->type == NODE_REDIRECT_IN && input)
		return (1);
	if (node->type == NODE_REDIRECT_OUT && output)
		return (1);
	if (node->type == NODE_REDIRECT_OUT_APPEND && output)
		return (1);
	return (0);
}

static void overwrite_stream(t_tree_node *node, t_shell *shell, int states_of_fd)
{
	char *filename;

	filename = execute_command_line(node->right, shell, 0);
	if (node->type == NODE_REDIRECT_IN)
		dup2()/// stopped here!
}

static int execute_redirection(t_tree_node *node, t_shell *shell, int states_of_fd)
{
	int input_state;
	int output_state;

	input_state = 0;
	output_state = 0;
	extract_states_of_fd(states_of_fd, &input_state, &output_state);
	if (!stream_is_overwritten(node, input_state, output_state))
	{
		overwrite_stream(node, shell, states_of_fd);
	}
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
		status = execute_redirection(node, shell, states_of_fds);
	else if (node->type == NODE_FILENAME)
	{

	}
	return (status);
}
