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

void	close_file(int fd)
{
	if (close(fd) == -1)
		perror("Error on closing a file\n"); //run error handler here
}

void free_and_reset_ptrs(int amount, void **ptr, ...)
{
	va_list	args;
	int i;

	va_start(args, ptr);
	i = 0;
	while (i < amount)
	{
		if (i > 0)
			ptr = va_arg(args, void **);
		if (*ptr)
		{
			free(*ptr);
			*ptr = NULL;
		}
		i++;
	}
	va_end(args);
}

int same_string(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) == ft_strlen(str2) 
			&& !ft_strncmp(str1, str2, ft_strlen(str1)))
			return (1);
	return (0);
}