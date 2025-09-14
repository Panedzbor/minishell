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
		status = env(shell->envp); //should return status
	else if (!ft_strncmp(cmd[0], "exit", 5))
		status = ft_printf("%s: found\n", cmd[0]); //should return status
	else
		status = call_external_command(cmd, shell);
	return (status);
}

static int execute_logic_operator(t_tree_node *node, t_shell *shell, int fd_in, int fd_out, int sub_pipe)
{
	int status;

	status = execute_command_line(node->left, shell, fd_in, fd_out, sub_pipe);
	if (status == 0 && node->type == NODE_AND)
		status = execute_command_line(node->right, shell, fd_in, fd_out, sub_pipe);
	else if (status != 0 && node->type == NODE_OR)
		status = execute_command_line(node->right, shell, fd_in, fd_out, sub_pipe);
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

static int execute_pipe(t_tree_node *node, t_shell *shell, int fd_in, int fd_out, int sub_pipe)
{
	int status;
	int fd[2];
	pid_t pid1;
	pid_t pid2;
	
	// (void) fd_in; (void) fd_out;
fprintf(stderr, "entered Pipe\n");fflush(stderr);
// fprintf(stderr, "in: %d out: %d\n", fd_in, fd_out);fflush(stderr);
// fprintf(stderr, "stdin: %d stdout: %d\n", STDIN_FILENO, STDOUT_FILENO);fflush(stderr);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid1 == 0)
	{
		fprintf(stderr, "fork1\n");fflush(stderr);
		// fprintf(stderr, "before dup: stdin: %d stdout: %d\n", STDIN_FILENO, STDOUT_FILENO);fflush(stderr);
		close(fd[0]);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		// fprintf(stderr, "after dup: in: %d out: %d\n", STDIN_FILENO, STDOUT_FILENO);fflush(stderr);
		close(fd[1]);
		status = execute_command_line(node->left, shell, STDIN_FILENO, STDOUT_FILENO, 1);
		exit(status);
	}
	if (!sub_pipe)
	{	
		pid2 = fork();
		if (pid2 < 0)
		{
			perror("fork");
			return (-1);
		}
		else if (pid2 == 0)
		{
			fprintf(stderr, "fork2\n");fflush(stderr);
			// fprintf(stderr, "before dup: stdin: %d stdout: %d\n", STDIN_FILENO, STDOUT_FILENO);fflush(stderr);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			// fprintf(stderr, "after dup: in: %d out: %d\n", STDIN_FILENO, STDOUT_FILENO);fflush(stderr);
			close(fd[0]);
			status = execute_command_line(node->right, shell, STDIN_FILENO, STDOUT_FILENO, 1);
			exit(status);
		}
	}
	else
	{
		fprintf(stderr, "no fork2\n");fflush(stderr);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd[0]);
		status = execute_command_line(node->right, shell, STDIN_FILENO, STDOUT_FILENO, 1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status)) //делать полную проверку сигналов
		return (WEXITSTATUS(status));
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

int execute_command_line(t_tree_node *node, t_shell *shell, int fd_in, int fd_out, int sub_pipe)
{
    int status;

	status = 0;
	if (node->type == NODE_COMMAND)
        status = validate_command(node, shell);
    else if (node->type == NODE_PIPE)
        status = execute_pipe(node, shell, fd_in, fd_out, sub_pipe);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		status = execute_logic_operator(node, shell, fd_in, fd_out, sub_pipe);
	return (status);
}
