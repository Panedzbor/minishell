#include "../includes/minishell.h"

static int detect_assignment(char *token)
{
    char *pos;

    pos = ft_strchr(token, '=');
    if (!pos || pos - token == 0)
        return (0);
    return (1);

}

void find_variable_assignments(t_token *token)
{
    t_token *current;
    int     type;

    current = token;
    while (current->next)
    {
        if (current->token_type == TOKEN_WORD
            && detect_assignment(current->value))
        {
            if (current->prev)
            {
                type = current->prev->token_type;
                if (type == TOKEN_AND || type == TOKEN_OR
                    || type == TOKEN_PAREN_LEFT || type == TOKEN_PIPE
                    || type == TOKEN_VAR_ASSIGN)
                    current->token_type = TOKEN_VAR_ASSIGN;
            }
            else
                current->token_type = TOKEN_VAR_ASSIGN;
        }
        current = current->next;
    }
}
