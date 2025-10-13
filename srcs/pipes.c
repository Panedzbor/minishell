#include "../includes/minishell.h"

static void create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		//return ;//launch error handler here
		exit(1);
	}
}

static void run_pipeline_stage(int fd_to_duplicate, int fd[2], t_tree_node *node, t_shell *shell)
{
	int status;
	//fprintf(stderr, "fork\n");
	status = run_cmd_in_current_process(fd_to_duplicate, fd, node, shell);
	clean_minishell(shell);
	exit(status);
}

int run_cmd_in_current_process(int fd_to_duplicate, int fd[2], t_tree_node *node, t_shell *shell)
{
	int status;

	if (fd_to_duplicate == STDOUT_FILENO)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		status = execute_command_line(node->left, shell, 1, 0/*?*/);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		status = execute_command_line(node->right, shell, 1, 0);
	}
	return (status);
}

static void close_fds(int fd[2], int sub_pipe)
{
	if (!sub_pipe)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

int execute_pipe(t_tree_node *node, t_shell *shell, int sub_pipe)
{
	int status;
	int fd[2];
	pid_t pid1;
	pid_t pid2;

	status = 0;
	create_pipe(fd);
	pid1 = create_subprocess();
	if (pid1 == 0)
		run_pipeline_stage(STDOUT_FILENO, fd, node, shell);
	if (!sub_pipe)
	{
		pid2 = create_subprocess();
		if (pid2 == 0)
			run_pipeline_stage(STDIN_FILENO, fd, node, shell);
	}
	else
		status = run_cmd_in_current_process(STDIN_FILENO, fd, node, shell);
	close_fds(fd, sub_pipe);
	wait_for_subprocess(pid1);
	if (!sub_pipe)
		wait_for_subprocess(pid2);
	return (status);
}
