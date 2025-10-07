#include "../includes/minishell.h"

static void expand_token_content(t_token *token, t_shell *shell)
{
	char	*exp;

	if (!token || !token->value || token->token_type != TOKEN_WORD)
		return;
	exp = expand_variables(token->value, shell);
	if (exp && ft_strncmp(token->value, exp, ft_strlen(token->value)) != 0)
	{
		free(token->value);
		token->value = exp;
	}else if(exp)
	{
		free(exp);
	}
}

void expand_tokens(t_token *token_list, t_shell *shell)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		expand_token_content(current, shell);
		current = current->next;
	}
}