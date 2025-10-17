#include "../includes/minishell.h"

static t_token *find_list_end(t_token *start)
{
	t_token *current;

	current = start;
	while (current->next->token_type != TOKEN_END_OF_LIST)
		current = current->next;
	return (current);
}

void check_if_token_sequence(t_token **priora, t_token **priora_end, t_token_type cur_token_type)
{
	t_token *temp;

	temp = NULL;
	if ((*priora)->token_type == cur_token_type)
	{
		temp = *priora;
		while ((*priora)->prev && (*priora)->prev->token_type == cur_token_type)
			*priora = (*priora)->prev;
	}
	if (temp && *priora != temp)
		*priora_end = temp;
}

t_token *find_lowest_priority(t_token *start, t_token *end)
{
	t_token *current;
	t_token *lowest;

	current = start;
	lowest = NULL;
	while (current != end)
	{
		if (!lowest)
			lowest = current;
		else if (current->priority <= lowest->priority)
			lowest = current;
		current = current->next;
	}
	if (start == end)
		lowest = start;
	if (current->priority <= lowest->priority)
		lowest = current;
	return (lowest);
}

static t_tree_node *fill_tree(t_token *start, t_token *end)
{
    t_tree_node *tree;
    t_token *left_branch[2];
    t_token *right_branch[2];
    t_token *parent;

    if (!start)
        return (NULL);
    ft_bzero(left_branch, 2 * sizeof(t_token *));
    ft_bzero(right_branch, 2 * sizeof(t_token *));
    if (!end)
        end = find_list_end(start);
    parent = divide_tokens(start, end, left_branch, right_branch);
    tree = create_tree_node(parent);
    tree->left = fill_tree(left_branch[0], left_branch[1]);
    tree->right = fill_tree(right_branch[0], right_branch[1]);
    return (tree);
}

int parser(char *input, t_shell *shell)
{
	t_tree_node *tree;

	tree = NULL;
	if (lexer(input, shell))
	{
		clean_session(shell);
		return (1);
	}
	expand_tokens(shell->tokens, shell);
	if (!analyze_parenthesis(shell->tokens, 0))
	{
		clean_session(shell);
		return (1);
	}
	if(shell->tokens)
	{
		if (valid_token_order(shell->tokens))
			tree = fill_tree(shell->tokens, NULL);
		else
			return (ms_err("error unexpected token\n", 1, d_err, shell));
	}
	shell->tree = tree;
	return (0);
}
