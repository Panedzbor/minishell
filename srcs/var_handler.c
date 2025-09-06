#include "../includes/minishell.h"

static char *check_name(char *var_name)
{
	char 	*name;
	char	*variable;
	size_t	var_len;

	variable = ft_strchr(var_name, '=');
	if(variable)
	{
		var_len = variable - var_name;
		name = ft_substr(var_name, 0, var_len);
		return name;
	}
	else
		return ft_strdup(var_name);
}

int search_var(char *var_name, char **var_store)
{
	size_t	i;
	size_t	var_len;
	char	*variable;
	char 	*name;

	i = 0;
	if (!var_store)
		return (-1);
	name = check_name(var_name);
	variable = ft_strjoin(name, "=");
	var_len = ft_strlen(variable);
	while (var_store[i])
	{
		if (ft_strncmp(variable, var_store[i], var_len) == 0)
		{
			free(variable);
			free(name);
			return i;
		}
		i++;
	}
	free(variable);
	free(name);
	return (-1);
}
char *get_var(char *var_name, char **var_store)
{
	size_t	var_len;
	size_t	len;
	char    *result;
    int     i;

	var_len = ft_strlen(var_name) + 1;
	i = search_var(var_name, var_store);
	if (i >= 0)
	{
		len = ft_strlen(var_store[i]) - var_len;
		result = (ft_substr(var_store[i], var_len, len));
		return(result);
	}
	return (NULL);
}

void set_var(char *variable, char ***var_store)
{  
    int i;

    i = search_var(variable, *var_store);
    if(i >= 0)
    {
        free((*var_store)[i]);
        (*var_store)[i] = ft_strdup(variable);
    }
    else
        *var_store = extend_arr(variable, *var_store);
}

void delete_var(char *var_name, char ***var_store)
{
	int	i;

	i = search_var(var_name, *var_store);
	if (i >=0)
		*var_store = shorten_arr((*var_store)[i], *var_store);
}
