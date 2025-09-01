#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell shell;
	t_tree_node *tree;

	(void)argc;
	(void)argv;
	shell.envp = envp;
	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		tree = parser(input);
		//draw_tree(tree);
		execute_command_line(tree, &shell);
	}
	return (0);
}
