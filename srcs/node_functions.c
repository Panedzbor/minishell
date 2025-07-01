#include "../includes/minishell.h"

node *create_node(char *data)
{
	node *new_node = (node *)malloc(sizeof(node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void validate_command(node* node)
{
	char *command;

	command = node->data;
	if (!ft_strncmp(command, "echo", 5))
	{
		ft_printf("%s\n", node->next->data);
	}
	else if (!ft_strncmp(command, "cd", 3))
		ft_printf("%s: found\n", command);
	else if (!ft_strncmp(command, "pwd", 4))
		ft_printf("%s: found\n", command);
	else if (!ft_strncmp(command, "export", 7))
		ft_printf("%s: found\n", command);
	else if (!ft_strncmp(command, "unset", 6))
		ft_printf("%s: found\n", command);
	else if (!ft_strncmp(command, "env", 4))
		ft_printf("%s: found\n", command);
	else if (!ft_strncmp(command, "exit", 5))
		ft_printf("%s: found\n", command);
	else
		ft_printf("%s: command not found\n", command);
}
