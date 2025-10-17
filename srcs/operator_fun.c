#include "../includes/minishell.h"

int	is_symbol_oper(char c)
{
	if ((c == '>') || (c == '<'))
		return (1);
	if ((c == '|') || (c == '&'))
		return (1);
	return (0);
}

static int	check_double(char *str)
{
	if (str[0] && str[1])
	{
		if (str[0] == str[1])
			return (1);
	}
	return (0);
}

static int	check_triple(char *str)
{
	if (str[1] && str[2])
	{
		if (str[1] == str[0] && str[2] == str[0])
			return (1);
	}
	return (0);
}

static t_token_type	get_token_type(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0 && str[2] == '\0')
		return (TOKEN_AND);
	if (ft_strncmp(str, "||", 2) == 0 && str[2] == '\0')
		return (TOKEN_OR);
	if (ft_strncmp(str, "<<", 2) == 0 && str[2] == '\0')
		return (TOKEN_REDIR_HERE_DOC);
	if (ft_strncmp(str, ">>", 2) == 0 && str[2] == '\0')
		return (TOKEN_REDIR_OUT_APPEND);
	if (ft_strncmp(str, "|", 1) == 0 && str[1] == '\0')
		return (TOKEN_PIPE);
	if (ft_strncmp(str, "<", 1) == 0 && str[1] == '\0')
		return (TOKEN_REDIR_IN);
	if (ft_strncmp(str, ">", 1) == 0 && str[1] == '\0')
		return (TOKEN_REDIR_OUT);
	return (TOKEN_WORD);
}

int	tokenize_oper(char **str, t_token **token_list, t_priora prior_map)
{
	char	*ptr;
	char	op[3];
	int		len;

	len = 0;
	ptr = *str;
	if (check_triple(ptr))
		return (1);
	else if (check_double(ptr))
	{
		op[0] = ptr[0];
		op[1] = ptr[1];
		op[2] = '\0';
		add_token(token_list, op, get_token_type(op), prior_map);
		len = 2;
	}
	else
	{
		op[0] = ptr[0];
		op[1] = '\0';
		add_token(token_list, op, get_token_type(op), prior_map);
		len = 1;
	}
	*str = ptr + len;
	return (0);
}
