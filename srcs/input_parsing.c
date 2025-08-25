#include "../includes/minishell.h"


void validate_command(t_tree_node *node)
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
		env();
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_printf("%s: found\n", cmd[0]);
	else
		call_external_command(cmd);
}

char **split_input(char *input)
{
	char **cmd_list;

	cmd_list = ft_split(input, '|');
	return (cmd_list);
}
