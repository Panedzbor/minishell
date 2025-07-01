#include "includes/minishell.h"

int	main(void)
{
	char *input;
	char **result;
	while (1)
	{
		input = readline("Minishell: ");
		result = ft_split(input, ' ');
		node* node = create_node(result[0]);
		node->next = create_node(result[1]);
		ft_printf("INFO: %s: node1 \n", node->data);
		ft_printf("INFO: %s: node2 \n", node->next->data);
		validate_command(node);
	}
	return (0);
}
