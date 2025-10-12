#include "../includes/minishell.h"

int open_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);//TODO replace hardcoded permission code with umask
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	// enter error handler here
	}
	return (fd);
}

void	close_file(int fd)
{
	if (close(fd) == -1)
		perror(""); 
	//run error handler here
}
