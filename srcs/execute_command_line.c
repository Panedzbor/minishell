#include "../includes/minishell.h"

static void validate_command(t_tree_node *node, t_shell *shell)
{
	char **cmd;

	cmd = node->argv;
	if (!ft_strncmp(cmd[0], "echo", 5))
		echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		cd(cmd[1]);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		printf("%s\n", pwd());
	else if (!ft_strncmp(cmd[0], "export", 7))
		ft_printf("%s: found\n", cmd[0]);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		ft_printf("%s: found\n", cmd[0]);
	else if (!ft_strncmp(cmd[0], "env", 4))
		env(shell->envp);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_printf("%s: found\n", cmd[0]);
	else
		call_external_command(cmd, shell);
}

void execute_command_line(t_tree_node *node, t_shell *shell)
{
    if (node->type == NODE_COMMAND)
        validate_command(node, shell);
    else if (node->type == NODE_PIPE)
        printf("PIPE\n");
    /* else if (node->type == NODE_VAR_ASSIGN)
		assign_variable(node, shell); */
}