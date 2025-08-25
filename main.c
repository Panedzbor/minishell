#include "includes/minishell.h"


int	main(void)
{
	char *input;
	// t_token *tokens;
	t_tree_node *tree; 

	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		tree = parser(input);
		//draw_tree(tree);
		execute_command_line(tree);
	}
	return (0);
}
