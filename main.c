#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell shell;
	t_tree_node *tree;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		tree = parser(input);
		execute_command_line(tree, &shell, 0, 0);
		//draw_tree(tree);
		//test_print_shell_vars(&shell);
		reset_streams(shell);
	}
	return (0);
}

