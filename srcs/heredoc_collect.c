#include "../includes/minishell.h"

void collect_heredocs(t_tree_node *node, t_shell *shell)
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