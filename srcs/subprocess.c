#include "../includes/minishell.h"

pid_t	create_subprocess(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);//launch error handler here
	}
	return (pid);
}

void	wait_for_subprocess(pid_t pid)
{
	int	status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status)) //делать полную проверку сигналов
		return /* (WEXITSTATUS(*status)) */;//launch error handler here
}
