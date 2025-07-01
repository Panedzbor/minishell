#include "includes/minishell.h"

int	main(void)
{
	char *input;
	node	*node;

	while (1)
	{
		input = readline("Minishell: ");
		if (!input)
			continue ;
		node = split_to_nodes(input);
		ft_printf("INFO: %s: node1 \n", node->data);
		ft_printf("INFO: %s: node2 \n", node->next->data);
		validate_command(node);
	}
	return (0);
}


