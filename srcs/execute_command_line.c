#include "../includes/minishell.h"

static int validate_command(t_tree_node *node, t_shell *shell)
{
	int status;
	char **cmd;


	cmd = node->argv;
	if (!ft_strncmp(cmd[0], "echo", 5))
		status = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		status = cd(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		status = pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		status = export(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		status = unset(cmd[1], shell);
	else if (!ft_strncmp(cmd[0], "env", 4))
		status = env(shell->envp);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		status = ft_printf("%s: found\n", cmd[0]);
	else
		status = call_external_command(cmd, shell);
	return (status);
}

static int execute_logic_operator(t_tree_node *node, t_shell *shell, int sub_pipe)
{
	int status;

	status = execute_command_line(node->left, shell, sub_pipe);
	if (status == 0 && node->type == NODE_AND)
		status = execute_command_line(node->right, shell, sub_pipe);
	else if (status != 0 && node->type == NODE_OR)
		status = execute_command_line(node->right, shell, sub_pipe);
	return (status);
}

/* static int assign_variable(t_tree_node *node, t_shell *shell)
{
	int i;

	i = 0;
	while (node->argv[i])
	{
		set_var(node->argv[i], &shell->local_vars);
		i++;
	}
	return (0);
} */

static pid_t create_subprocess(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);//launch error handler here
	}
	return (pid);
}

static int run_cmd_in_current_process(int fd_to_duplicate, int fd[2], t_tree_node *node, t_shell *shell)
{
	int status;

	if (fd_to_duplicate == STDOUT_FILENO)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		status = execute_command_line(node->left, shell, 1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		status = execute_command_line(node->right, shell, 1);
	}
	return (status);
}

static void create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;//launch error handler here
	}
}

static void wait_for_subprocess(pid_t pid)
{
	int status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status)) //делать полную проверку сигналов
		return /* (WEXITSTATUS(*status)) */;//launch error handler here
}

static void execute_subprocess(int fd_to_duplicate, int fd[2], t_tree_node *node, t_shell *shell)
{
	int status;
	//fprintf(stderr, "fork\n");
	status = run_cmd_in_current_process(fd_to_duplicate, fd, node, shell);
	exit(status);
}

static void close_fds(int fd[2], int sub_pipe)
{
	if (!sub_pipe)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

static int execute_pipe(t_tree_node *node, t_shell *shell, int sub_pipe)
{
	int status;
	int fd[2];
	pid_t pid1;
	pid_t pid2;

	create_pipe(fd);
	pid1 = create_subprocess();
	if (pid1 == 0)
		execute_subprocess(STDOUT_FILENO, fd, node, shell);
	if (!sub_pipe)
	{	
		pid2 = create_subprocess();
		if (pid2 == 0)
			execute_subprocess(STDIN_FILENO, fd, node, shell);
	}
	else
		status = run_cmd_in_current_process(STDIN_FILENO, fd, node, shell);
	close_fds(fd, sub_pipe);
	wait_for_subprocess(pid1);
	if (!sub_pipe)
		wait_for_subprocess(pid2);
	return (status);
}

int execute_command_line(t_tree_node *node, t_shell *shell, int sub_pipe)
{
    int status;

	status = 0;
	if (node->type == NODE_COMMAND)
        status = validate_command(node, shell);
    else if (node->type == NODE_PIPE)
        status = execute_pipe(node, shell, sub_pipe);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		status = execute_logic_operator(node, shell, sub_pipe);
	return (status);
}
