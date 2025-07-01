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
