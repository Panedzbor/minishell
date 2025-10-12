#include "../includes/minishell.h"

int	ft_arr_el_count(void **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	len;
	int	i;

	i = 0;
	len = ft_arr_el_count((void **)arr);
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**extend_arr(char *ext_str, char **arr)
{
	char	**result;
	int		str_count;
	int		i;

	str_count = ft_arr_el_count((void **)arr);
	result = (char **)ft_calloc(str_count + 2, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			result[i] = ft_strdup(arr[i]);
			i++;
		}
	}
	result[i] = ft_strdup(ext_str);
	result[i + 1] = NULL;
	free_arr(arr);
	return (result);
}

char	**shorten_arr(char *del_str, char **arr)
{
	char	**result;
	int		str_count;
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_count = ft_arr_el_count((void **)arr);
	len = ft_strlen(del_str);
	result = (char **)ft_calloc(str_count, sizeof(char *));
	if (!result)
		return (NULL);
	while (arr[i])
	{
		if (ft_strncmp(arr[i], del_str, len) != 0)
		{
			result[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	result[j] = NULL;
	free_arr(arr);
	return (result);
}

char	**ft_charrdup(char **arr)
{
	int		count;
	char	**dupl;
	int		i;

	count = 0;
	while (arr[count])
		count++;
	dupl = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!check_alloc(dupl))
		return (NULL);
	i = 0;
	while (i < count)
	{
		dupl[i] = ft_strdup(arr[i]);
		i++;
	}
	dupl[count] = NULL;
	return (dupl);
}
