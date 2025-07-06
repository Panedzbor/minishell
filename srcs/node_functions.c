#include "../includes/minishell.h"

node *create_node(char *data)
{
	node *new_node;

	new_node = (node *)malloc(sizeof(node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}


void	add_node(node **head, char* data)
{
	node	*new_node;
	node	*temp;

	new_node = create_node(data);
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

node	*split_to_nodes(char *str, char delimiter)
{
	char	**splitted;
	node	*first_node;
	int		i;

	first_node = NULL;
	splitted = ft_split(str, delimiter);
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