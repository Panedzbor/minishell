#include "../includes/minishell.h"

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

int open_file(char *filename, int flags)
{
	int fd;

	fd = open(filename, flags, 0644);//TODO replace hardcoded permission code with umask
	if (fd == -1)
	{
		perror("error on opening the file\n");
		return (-1);// enter error handler here
	}
	return (fd);
}