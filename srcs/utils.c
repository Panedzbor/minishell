#include "../includes/minishell.h"

int	check_operator(char *token)
{
	size_t	len;

	len = ft_strlen(token);
	if (!ft_strncmp("|", token, len))
		return (1);
	else if (!ft_strncmp("<", token, len))
		return (2);
	else if (!ft_strncmp(">", token, len))
		return (3);
	else if (!ft_strncmp("<<", token, len))
		return (4);
	else if (!ft_strncmp(">>", token, len))
		return (5);
	return (0);
}

int	same_string(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) == ft_strlen(str2) 
		&& !ft_strncmp(str1, str2, ft_strlen(str1)))
		return (1);
	return (0);
}

char	*trim_quotes(char *str, int *quoted)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 1)
	{
		if ((str[0] == '\"' && str[len - 1] == '\"')
			|| (str[0] == '\'' && str[len - 1] == '\''))
		{
			*quoted = 1;
			return (ft_substr(str, 1, len - 2));
		}
	}
	return (ft_strdup(str));
}
