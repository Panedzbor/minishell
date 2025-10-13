#include "../includes/minishell.h"

char *get_exp_var_val(char *var_name, t_shell *shell)
{
	char *value;

	if (!var_name)
		return (NULL);
	if (ft_strncmp(var_name, "?", 1) == 0 && ft_strlen(var_name) == 1)
		value = ft_itoa(shell->status_code);
	else
		value = get_var(var_name, shell->envp);
	return (value);
}

static int expand_var_len(char *str, int i, t_shell *shell, size_t *res_len)
{
	char *var_nam;
	char *var_val;
	size_t name_len;

	var_nam = get_exp_var_nam(str, i + 1, &name_len);
	if (!var_nam)
		return (i + 1);
	var_val = get_exp_var_val(var_nam, shell);
	if (var_val)
	{
		*res_len -= (1 + name_len);
		*res_len += ft_strlen(var_val);
		free(var_val);
	}
	else
		*res_len -= (1 + name_len);
	free(var_nam);
	return (i + 1 + name_len);
}

size_t calc_res_len(char *str, t_shell *shell)
{
	size_t res_len;
	int i;
	char quote;

	i = 0;
	quote = 0;
	res_len = ft_strlen(str);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
		{
			quote = str[i];
			i++;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '$' && quote != '\'')
			i = expand_var_len(str, i, shell, &res_len);
		else
			i++;
	}
	return (res_len);
}
