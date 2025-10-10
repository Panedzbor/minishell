#include "../includes/minishell.h"

int open_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);//TODO replace hardcoded permission code with umask
	if (fd == -1)
	{
		perror("error on opening the file\n");
		return (-1);
	// enter error handler here
	}
	return (fd);
}

void	close_file(int fd)
{
	if (close(fd) == -1)
		perror("Error on closing a file\n"); 
	//run error handler here
}
