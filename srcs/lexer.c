#include "../includes/minishell.h"

static int	is_parenth(char c)
{
	if ((c == '(') || (c == ')'))
		return (1);
	return (0);
}

static int	is_word(char c, char *quote)
{
	if ((c == '"' || c == '\'') && !(*quote))
	{
		*quote = c;
		return (1);
	}
	if (!(*quote))
	{
		if (c == ' ' || c == '\t')
			return (0);
		if (is_parenth(c) || is_symbol_oper(c))
			return (0);
	}
	else if (c == *quote)
	{
		*quote = 0;
		return (1);
	}
	if (c == '\0')
		return (0);
	return (1);
}

static void	tokenize_parenth(char **str, t_token **tokens, t_priora prior_map)
{
	char	*ptr;

	ptr = *str;
	if (ptr[0] == '(')
		add_token(tokens, "(", TOKEN_PAREN_LEFT, prior_map);
	else
		add_token(tokens, ")", TOKEN_PAREN_RIGH, prior_map);
	*str = ptr + 1;
}

static int	tokenize_word(char **str, t_token **tokens, t_priora priority_map)
{
	char	*start;
	char	*result;
	char	quote;

	result = NULL;
	quote = 0;
	start = *str;
	while (is_word(**str, &quote))
		(*str)++;
	if (!quote)
		result = ft_substr(start, 0, *str - start);
	else
		return (1);
	if (result)
	{
		add_token(tokens, result, TOKEN_WORD, priority_map);
		free(result);
	}
	return (0);
}

int	lexer(char *input, t_shell *shell)
{
	t_token		*list;
	char		*ptr;
	t_priora	prior_map;

	init_token_priority(&prior_map);
	ptr = input;
	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '\t')
		{
			ptr++;
			continue ;
		}
		else if (is_symbol_oper(*ptr) 
			&& tokenize_oper(&ptr, &shell->tokens, prior_map))
			return (ms_err("error unexpected token\n", 1, d_err, shell));
		else if (is_parenth(*ptr))
			tokenize_parenth(&ptr, &shell->tokens, prior_map);
		else if (tokenize_word(&ptr, &shell->tokens, prior_map))
			return (ms_err("error unclosed quotes\n", 1, d_err, shell));
	}
	add_token(&list, NULL, TOKEN_END_OF_LIST, prior_map);
	return (0);
}
