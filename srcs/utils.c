#include "../includes/minishell.h"

void check_process(pid_t pid)
{
	if (pid < 0)
	{
		printf("Fork failed\n");
		exit(1);
	}
	else if (pid > 0)
	{
		wait(NULL);
		return;
	}
}

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