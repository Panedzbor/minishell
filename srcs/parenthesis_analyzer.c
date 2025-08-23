#include "../includes/minishell.h"

static t_token *check_closed_parenths(t_token *last, int parenth_open)
{
    if (parenth_open)
        return (NULL);
    return (last);
}

t_token *analyze_parenthesis(t_token *tokens, int parenth_open)
{
    t_token *current;
    static int parenth_level;

    current = tokens;
    while (current->token_type != TOKEN_END_OF_LIST)
    {
        if (parenth_open && current->token_type == TOKEN_PAREN_RIGH)
            return (current);
        if (!parenth_open && current->token_type == TOKEN_PAREN_RIGH)
            return (NULL);
        if (parenth_open)
            current->priority += parenth_level;
        if (current->token_type == TOKEN_PAREN_LEFT)
        {
            parenth_level += 10;
            current = analyze_parenthesis(current->next, 1);
            if (!current)
                return (NULL);
            parenth_level -= 10;
            current->priority += parenth_level;
        }
        current = current->next;
    }
    return (check_closed_parenths(current, parenth_open));
}

