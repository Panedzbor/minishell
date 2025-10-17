#include "../includes/minishell.h"

void	add_token(t_token **head, char *value, 
			t_token_type type, t_priora prior_map)
{
	t_token	*token;
	t_token	*tmp_token;

	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->token_type = type;
	token->priority = get_token_priority(type, prior_map);
	token->value = NULL;
	if (value)
		token->value = ft_strdup(value);
	token->next = NULL;
	token->prev = NULL;
	if (!*head)
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

int	get_token_priority(t_token_type type, t_priora priority_map)
{
	int	i;

	i = 0;
	while (priority_map.value[i] > 0)
	{
		if (type == priority_map.type[i])
			return (priority_map.value[i]);
		i++;
	}
	return (-1);
}

void	init_token_priority(t_priora *prior)
{
	prior->type[0] = TOKEN_AND;
	prior->value[0] = 1;
	prior->type[1] = TOKEN_OR;
	prior->value[1] = 1;
	prior->type[2] = TOKEN_PIPE;
	prior->value[2] = 2;
	prior->type[3] = TOKEN_REDIR_IN;
	prior->value[3] = 3;
	prior->type[4] = TOKEN_REDIR_HERE_DOC;
	prior->value[4] = 3;
	prior->type[5] = TOKEN_REDIR_OUT;
	prior->value[5] = 3;
	prior->type[6] = TOKEN_REDIR_OUT_APPEND;
	prior->value[6] = 3;
	prior->type[7] = TOKEN_PAREN_LEFT;
	prior->value[7] = 4;
	prior->type[8] = TOKEN_PAREN_RIGH;
	prior->value[8] = 4;
	prior->type[9] = TOKEN_WORD;
	prior->value[9] = 5;
	prior->type[10] = TOKEN_END_OF_LIST;
	prior->value[10] = -1;
}

int	valid_token_order(t_token *list)
{
	t_token	*cur;

	if (list->token_type != TOKEN_WORD)
		return (0);
	cur = list;
	while (cur->token_type != TOKEN_END_OF_LIST)
	{
		if (cur->token_type != TOKEN_WORD 
			&& cur->next->token_type != TOKEN_WORD)
			return (0);
		cur = cur->next;
	}
	return (1);
}
