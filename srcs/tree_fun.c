#include "../includes/minishell.h"

t_tree_node *new_node(t_type_node type)
{
	t_tree_node *node = malloc(sizeof(t_tree_node));
	// add free
	if (!node)
		return (NULL);
	node->type = type;
	node->argv = NULL;
	//node->file_name = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
