#include "../includes/minishell.h"

void add_token(t_token **head, char *value, t_token_type type)
{
    t_token *token;
    t_token *tmp_token; 

    token = malloc(sizeof(t_token));
    if(!token)
        return ;
    token->token_type = type;
    token->value = ft_strdup(value);
    token->next = NULL;
    token->prev = NULL;
    if(!*head)
    {
        *head = token;
        return ;
    }
        tmp_token = *head;
        while (tmp_token->next)
            tmp_token = tmp_token->next;
        tmp_token->next = token;
        token->prev = tmp_token;
}
