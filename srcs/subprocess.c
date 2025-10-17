#include "../includes/minishell.h"

pid_t	create_subprocess(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("failed process fork\n", D_ERR);
		return (-1);
	}
	return (pid);
}

void	wait_for_subprocess(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return ;
}

static	int	check_and_wait_for_pid(pid_t pid)
{
	int	status;

	status = 0;
	if (pid < 0)
	{
		ft_putstr_fd("failed process fork\n", D_ERR);
		status = -1;
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	return (status);
}

pid_t	fork_and_get_pid(int *status)
{
	pid_t	pid;

	pid = fork();
	*status = check_and_wait_for_pid(pid);
	return (pid);
}
