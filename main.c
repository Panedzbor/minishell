#include "includes/minishell.h"

int	main(void)
{
	char *input;
	t_token *tokens;
	t_tree_node *tree;
	//char	**splitted;
	//t_node	*first_node;
	//tokens = NULL;
	//tree = NULL;
	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		tokens = lexer(input);
		print_tokens(tokens);
		if (!analyze_parenthesis(tokens, 0))
			printf("Error\n");
		test_anal_parent(tokens);
		/* tree =  */fill_tree(tokens, NULL);
		//splitted = split_input(input);
		//first_node = create_cmd_list(splitted);
		//test_list_data(first_node);
		//validate_command(first_node);
	}
	return (0);
}




