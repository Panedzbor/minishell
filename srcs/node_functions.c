#include "../includes/minishell.h"

t_node *create_node(char *command)
{
	t_node *new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->command = ft_split(command, ' ');
	if (!new_node->command)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

void	add_node_to_list(t_node **head, char *command)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = create_node(command);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

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

t_node	*create_cmd_list(char **commands)
{
	/*char	**splitted;*/
	t_node	*first_node;
	int		i;

	first_node = NULL;
	/*splitted = ft_split(str, delimiter);
	if (!splitted)
		return (NULL);*/
	i = 0;
	while (commands[i])
	{
		add_node_to_list(&first_node, commands[i]);
		i++;
	}
	//free_split(splitted);
	return (first_node);
}
