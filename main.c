#include "includes/minishell.h"

int	main(void)
{
	char *input;
	t_token *token = NULL;
	//char	**splitted;
	//t_node	*first_node;

	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		token = lexer(input);
		print_tokens(token);
		//splitted = split_input(input);
		//first_node = create_cmd_list(splitted);
		//test_list_data(first_node);
		//validate_command(first_node);
	}
	return (0);
}




