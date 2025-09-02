#include "../includes/minishell.h"

char *search_var(char *var_name, char **var_store)
{
	size_t	i;
	size_t	var_len;
	char	*variable;

	i = 0;
	variable = ft_strjoin(var_name, "=");
	var_len = ft_strlen(variable);
	while (var_store[i])
	{
		if (ft_strncmp(variable, var_store[i], var_len) == 0)
		{
			free(variable);
			return var_store[i];
		}
		i++;
	}
	free(variable);
	return NULL;
}

void set_var(char *var_name, char **var_store)
{
	char	*result;

	result = search_var(var_name, var_store);
	if (!result)
		*var_store = extend_arr(var_store, result);
}

char *get_var(char *var_name, char **var_store)
{
	size_t	var_len;
	size_t	len;
	char	*variable;
	char	*result;

	variable = ft_strjoin(var_name, "=");
	var_len = ft_strlen(variable);
	result = search_var(var_name, var_store);
	if (result)
	{
		len = ft_strlen(result) - var_len;
		return (ft_substr(result, var_len, len));
	}
	return (NULL);
}

void delete_var(char *var_name, char **var_store)
{
	char	*result;

	result = search_var(var_name, var_store);
	if (result)
		*var_store = shorten_arr(var_store, result);
}
