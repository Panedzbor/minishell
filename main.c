#include "includes/minishell.h"

static void collect_heredocs(t_tree_node *node, t_shell *shell)
{
	char *heredoc_file;
	
	if (node->left)
		collect_heredocs(node->left, shell);
	if (node->type != NODE_REDIRECT_HERE_DOC)
	{
		if (node->right)
			collect_heredocs(node->right, shell);
		return ;
	}
	heredoc_file = run_here_doc(node->right->argv[0], shell);
	node->right->argv[0] = heredoc_file; 
	//prev argv[0] is a value from token list - no need to free here. But if parser will be changed to duplicate token list values, then free here.
}

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
		tree = parser(input);
		free(input);
		//draw_tree(tree);
		collect_heredocs(tree, &shell);
		execute_command_line(tree, &shell, 0, 0);
		//test_print_shell_vars(&shell);
		reset_streams(shell);
	}
	return (0);
}

