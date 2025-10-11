#include "../includes/minishell.h"

static int	copy_var_value(char *result, int pos, char *var_value)
{
	int	len;
	int	i;

	i = 0;
	if (!var_value)
		return (pos);
	len = ft_strlen(var_value);
	while (i < len)
	{
		result[pos + i] = var_value[i];
		i++;
	}
	return (pos + len);
}

static int	handle_var(char *str, int *str_pos, char *result, t_shell *shell)
{
	char	*var_nam;
	char	*var_val;
	size_t	name_len;
	int		res_pos;

	res_pos = 0;
	var_nam = get_exp_var_nam(str, *str_pos + 1, &name_len);
	if (!var_nam)
	{
		result[res_pos] = str[*str_pos];
		res_pos++;
		(*str_pos)++;
		return (res_pos);
	}
	var_val = get_exp_var_val(var_nam, shell);
	res_pos = copy_var_value(result, res_pos, var_val);
	if (var_val && ft_strncmp(var_nam, "?", 1) == 0 && ft_strlen(var_nam) == 1)
		free(var_val);
	free(var_nam);
	*str_pos += 1 + name_len;
	return (res_pos);
}

static void	increment(char *str, char *result, int *str_pos, int *res_pos)
{
	result[*res_pos] = str[*str_pos];
	(*res_pos)++;
	(*str_pos)++;
}

static void	build_result(char *str, char *result, t_shell *shell)
{
	int		str_pos;
	int		res_pos;
	char	quote;

	str_pos = 0;
	res_pos = 0;
	quote = 0;
	while (str[str_pos])
	{
		if ((str[str_pos] == '\'') && !quote)
		{
			quote = str[str_pos];
			increment(str, result, &str_pos, &res_pos);
		}
		else if (str[str_pos] == quote)
		{
			quote = 0;
			increment(str, result, &str_pos, &res_pos);
		}
		else if (str[str_pos] == '$' && quote != '\'')
			res_pos += handle_var(str, &str_pos, result + res_pos, shell);
		else
			increment(str, result, &str_pos, &res_pos);
	}
	result[res_pos] = '\0';
}

char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;
	size_t	res_len;

	if (!str)
		return (NULL);
	res_len = calc_res_len(str, shell);
	result = malloc(res_len + 1);
	if (!result)
		return (NULL);
	build_result(str, result, shell);
	return (result);
}
