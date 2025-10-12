#include "../includes/minishell.h"

static char *remove_quotes(char *str)
{
	char *result;
	char *start;
	char quote;

	result = (char *)malloc(ft_strlen(str) + 1);
	start = result;
	if (!result)
		return (NULL);
	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (quote && *str == quote)
			quote = 0;
		else
		{
			*result = *str;
			result ++;
		}
		str++;
	}
	*result = '\0';
	return (start);
}
void remove_quotes_from_argv(char **argv)
{
	int i;
	char *new_arg;

	i = 0;
	while (argv[i])
	{
		new_arg = remove_quotes(argv[i]);
		if (new_arg)
		{
			free(argv[i]);
			argv[i] = new_arg;
		}
		i++;
	}
}
