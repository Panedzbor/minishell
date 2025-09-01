#include "../includes/minishell.h"

int check_process(pid_t pid)
{
	int status;

	if (pid < 0)
	{
		printf("Fork failed\n");
		status = -1;
		//exit(1);
	}
	else if (pid > 0)
	{
		wait(&status);
		status = WEXITSTATUS(status);
	}
	return (status);
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
