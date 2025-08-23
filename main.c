#include "includes/minishell.h"


int	main(void)
{
	char *input;
	t_token *tokens;
	t_tree_node *tree;

	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		tokens = lexer(input);
		test_print_tokens(tokens);
		if (!analyze_parenthesis(tokens, 0))
			printf("Error\n");
		tree = fill_tree(tokens, NULL);
		draw_tree(tree);
	}
	return (0);
}
