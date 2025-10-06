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
		input = readline("Minishell: ");//TODO multiline input
		add_history((const char*)input);
		if (!input || same_string(input, ""))
			continue ;
		tree = parser(input, &shell);
		free(input);
		//draw_tree(tree);
		collect_heredocs(tree, &shell);
		execute_command_line(tree, &shell, 0, 0);
		//test_print_shell_vars(&shell);
		clean_session(&shell);
		reset_streams(shell);
	}
	return (0);
}

