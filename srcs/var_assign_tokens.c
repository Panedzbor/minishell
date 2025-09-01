#include "../includes/minishell.h"

static int detect_assignment(char *token)
{
    char *pos;

    pos = ft_strchr(token, '=');
    if (!pos || pos - token == 0)
        return (0);
    return (1);

}

static int delete_token(t_token **current, t_token **head)
{
    t_token *to_del;
    
    to_del = *current;
    *current = to_del->next;
    if(to_del->prev)
    {
        (*current)->prev = to_del->prev;
        (*current)->prev->next = *current;
    }
    else
    {
        *head = *current;
        (*head)->prev = NULL;
    }
    free(to_del->value);
    free(to_del);
    return (1);
}

static int loop_through_subsequent_tokens(t_token **current, t_token **head)
{
    t_token *subsequent;
    t_token_type stt;
    int del;

    subsequent = (*current)->next;
    del = 0;
    while (subsequent->token_type != TOKEN_END_OF_LIST)
    {
        stt = subsequent->token_type;
        if (stt == TOKEN_AND || stt == TOKEN_OR || stt == TOKEN_PIPE)
            break ;
        else if (stt == TOKEN_WORD)
        {
            del = delete_token(current, head);
            break ;
        }
        subsequent = subsequent->next;
    }
    return (del);
}

static void remove_ignored_assignments(t_token **list)
{
    t_token *current;
    int     token_deleted;

    current = *list;
    while (current->token_type != TOKEN_END_OF_LIST)
    {
        token_deleted = 0;
        if (current->token_type == TOKEN_VAR_ASSIGN)
            token_deleted = loop_through_subsequent_tokens(&current, list);
        if (!token_deleted)
            current = current->next;
    }
}

void find_variable_assignments(t_token **token)
{
    t_token *current;
    int     type;

    current = *token;
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
    remove_ignored_assignments(token);
}
