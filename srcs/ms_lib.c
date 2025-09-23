#include "../includes/minishell.h"

char *ms_strjoin(const char *s1, const char *s2)
{
	char *result;

	result = ft_strjoin(s1, s2);
	check_ptr(result);
	return (result);
}

char *ms_strdup(const char *str)
{
	char *result;

	result = ft_strdup(str);
	check_ptr(result);
	return (result);
}