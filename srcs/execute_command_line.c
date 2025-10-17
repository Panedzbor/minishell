#include "../includes/minishell.h"

static int	validate_command(t_tree_node *node, t_shell *shell)
{
	int		status;
	char	**cmd;

	remove_quotes_from_argv(node->argv);
	cmd = node->argv;
	if (!ft_strncmp(cmd[0], "echo", 5))
		status = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		status = ms_cd(cmd, shell);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		status = pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		status = export(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		status = unset(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "env", 4))
		status = env(shell->envp);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		status = ms_exit(cmd, shell);
	else
		status = call_external_command(cmd, shell);
	return (status);
}

static int	execute_logic_operator(t_tree_node *node, t_shell *sh, int sub_pipe)
{
	int	status;

	status = execute_command_line(node->left, sh, sub_pipe, 0);
	if (status == 0 && node->type == NODE_AND)
		status = execute_command_line(node->right, sh, sub_pipe, 0);
	else if (status != 0 && node->type == NODE_OR)
		status = execute_command_line(node->right, sh, sub_pipe, 0);
	return (status);
}

int	execute_command_line(t_tree_node *node, t_shell *sh, int sub_pipe, int streams)
{
	int status;

	status = 0;
	if (node->type == NODE_COMMAND)
		status = validate_command(node, sh);
	else if (node->type == NODE_PIPE)
		status = execute_pipe(node, sh, sub_pipe);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		status = execute_logic_operator(node, sh, sub_pipe);
	else if (node->type == NODE_REDIRECT_IN || node->type == NODE_REDIRECT_HERE_DOC 
	|| node->type == NODE_REDIRECT_OUT || node->type == NODE_REDIRECT_OUT_APPEND)
		status = execute_redirection(node, sh, streams);
	return (status);
}
