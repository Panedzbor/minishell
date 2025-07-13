#include "includes/minishell.h"

int	main(void)
{
	char *input;
	t_node	*inp_node;

	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		inp_node = split_to_nodes(input, ' ');
		test_list_data(inp_node);
		validate_command(inp_node);
	}
	return (0);
}


