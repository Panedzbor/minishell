#include "../includes/minishell.h"

int	valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static char	*get_spec_var_nam(char c, size_t *name_len)
{
	char	*var_name;

	if (c != '?')
		return (NULL);
	*name_len = 1;
	var_name = malloc(2);
	if (!var_name)
		return (NULL);
	var_name[0] = '?';
	var_name[1] = '\0';
	return (var_name);
}

static char	*get_norm_var_nam(char *str, int pos, size_t *name_len)
{
	size_t	len;
	size_t	i;
	char	*var_name;

	i = 0;
	len = 0;
	while (str[pos + len] && valid_var_char(str[pos + len]))
		len++;
	if (len == 0)
	{
		*name_len = 0;
		return (NULL);
	}
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	while (i < len)
	{
		var_name[i] = str[pos + i];
		i++;
	}
	var_name[i] = '\0';
	*name_len = len;
	return (var_name);
}

char	*get_exp_var_nam(char *str, int pos, size_t *name_len)
{
	char	*var_name;

	var_name = get_spec_var_nam(str[pos], name_len);
	if (var_name)
		return (var_name);
	return (get_norm_var_nam(str, pos, name_len));
}
