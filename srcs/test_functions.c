#include "../includes/minishell.h"

void test_list_data(t_node *test_node)
{
	int i;

	i = 1;
	while (test_node)
	{
		ft_printf("INFO:  Node #%d: %s\n", i, test_node->data);
		test_node = test_node->next;
		i++;
	}
}
