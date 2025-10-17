#include "../includes/minishell.h"

void	*collect_heredocs(t_tree_node *node, t_shell *shell)
{
	char	*heredoc_file;

	if (node->left)
		collect_heredocs(node->left, shell);
	if (node->type != NODE_REDIR_HERE_DOC)
	{
		if (node->right)
			collect_heredocs(node->right, shell);
		return (node);
	}
	heredoc_file = run_here_doc(node->right->argv[0], shell);
	if (!heredoc_file)
	{
		clean_session(shell);
		reset_streams(*shell);
		return (NULL);
	}
	if (node->right && node->right->argv && node->right->argv[0])
		free(node->right->argv[0]);
	node->right->argv[0] = heredoc_file;
	return (heredoc_file);
}
