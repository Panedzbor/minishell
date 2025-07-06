#include "includes/minishell.h"

int	main(void)
{
	char *input;
	char *variable;
	node	*inp_node;
	node	*env_node;

	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		//TEST INPUT
		inp_node = split_to_nodes(input, ' ');
		test_list_data(inp_node);
		validate_command(inp_node);

		//TEST_ENV_PATH
		variable = seach_env_var("PATH");
		env_node = split_to_nodes(variable, ':');
		test_list_data(env_node);
	}
	return (0);
}


