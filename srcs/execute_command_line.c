#include "../includes/minishell.h"

static int validate_command(t_tree_node *node, t_shell *shell)
{
	int status;
	char **cmd;

	cmd = node->argv;
	if (!ft_strncmp(cmd[0], "echo", 5))
		status = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		status = cd(cmd[1]);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		status = pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		status = export(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		status = unset(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "env", 4))
		env(shell->envp); //should return status
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_printf("%s: found\n", cmd[0]); //should return status
	else
		status = call_external_command(cmd, shell);
	return (status);
}

static int execute_logic_operator(t_tree_node *node, t_shell *shell)
{
	int status;

	status = execute_command_line(node->left, shell);
	if (status == 0 && node->type == NODE_AND)
		status = execute_command_line(node->right, shell);
	else if (status != 0 && node->type == NODE_OR)
		status = execute_command_line(node->right, shell);
	return (status);
}

int execute_command_line(t_tree_node *node, t_shell *shell)
{
    int status;

	if (node->type == NODE_COMMAND)
        status = validate_command(node, shell);
    else if (node->type == NODE_PIPE)
        printf("PIPE\n");
    /* else if (node->type == NODE_VAR_ASSIGN)
		assign_variable(node, shell); */
	else if (node->type == NODE_AND || node->type == NODE_OR)
		status = execute_logic_operator(node, shell);
	return (status);
}