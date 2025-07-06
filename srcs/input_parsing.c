#include "../includes/minishell.h"

/*static void	free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free (splitted[i]);
		i++;
	}
	free (splitted[i]);
	free (splitted);
}*/

node	*split_to_nodes(char *input)
{
	char	**splitted;
	node	*first_node;
	int		i;

	first_node = NULL;
	splitted = ft_split(input, ' ');
	if (!splitted)
		return (NULL);
	i = 0;
	while (splitted[i])
	{
		add_node(&first_node, splitted[i]);
		i++;
	}
	//free_split(splitted);
	return (first_node);
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
		env();
	else if (!ft_strncmp(command, "exit", 5))
		ft_printf("%s: found\n", command);
	else
		ft_printf("%s: command not found\n", command);
}
