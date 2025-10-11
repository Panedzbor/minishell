#include "../includes/minishell.h"

static void	free_token(t_token *token)
{
	t_token *current;
	t_token *next;

	current = token;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

static void	free_tree(t_tree_node *tree)
{
	if (!tree)
		return;
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	if (tree->argv)
		free_arr(tree->argv);
	free(tree);
}

void	clean_session(t_shell *shell)
{
	if (shell->tree)
	{
		free_tree(shell->tree);
		shell->tree = NULL;
	}
	if (shell->tokens)
	{
		free_token(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cur_input_stream > 0)
		close(shell->cur_input_stream);
	if (shell->cur_output_stream > 0)
		close(shell->cur_output_stream);
}

void	clean_minishell(t_shell *shell)
{
	clean_session(shell);
	if (shell->envp)
	{
		free_arr(shell->envp);
		shell->envp = NULL;
	}
	if (shell->local_vars)
	{
		free_arr(shell->local_vars);
		shell->local_vars = NULL;
	}
	if (shell->def_input_stream > 0)
		close(shell->def_input_stream);
	if (shell->def_output_stream > 0)
		close(shell->def_output_stream);
}
