#include "../includes/minishell.h"

void add_token(t_token **head, char *value, t_token_type type, t_priora prior_map)
{
    t_token *token;
    t_token *tmp_token; 

    token = malloc(sizeof(t_token));
    if(!token)
        return ;
    token->token_type = type;
    token->priority = get_token_priority(type, prior_map);
    if (value)
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

int get_token_priority(t_token_type type, t_priora priority_map)
{
    int i;

    i = 0;
    while (priority_map.value[i] > 0)
    {
        if (type == priority_map.type[i])
            return (priority_map.value[i]);
        i++;
    }
    return (-1);
}