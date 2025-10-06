#include "../includes/minishell.h"

static void expand_token_content(t_token *token, t_shell *shell)
{
    char *expanded;

    if (!token || !token->value || token->token_type != TOKEN_WORD)
        return;
    expanded = expand_variables(token->value, shell);
    if (expanded)
    {
        free(token->value);
        token->value = expanded;
    }
}

void expand_tokens(t_token *token_list, t_shell *shell)
{
    t_token *current;

    current = token_list;
    while (current)
    {
        expand_token_content(current, shell);
        current = current->next;
    }
}