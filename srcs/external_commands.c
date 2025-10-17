#include "../includes/minishell.h"

static char	*search_in_dir(DIR *command_dir, char *cmd, char *path)
{
	char			*full_path;
	char			*temp;
	struct dirent	*info_dir;

	info_dir = readdir(command_dir);
	while (info_dir)
	{
		if (ft_strlen(cmd) != ft_strlen(info_dir->d_name))
		{
			info_dir = readdir(command_dir);
			continue ;
		}
		if (!ft_strncmp(cmd, info_dir->d_name, ft_strlen(cmd)))
		{
			temp = ft_strjoin(path, "/");
			full_path = ft_strjoin(temp, cmd);
			free(temp);
			return (full_path);
		}
		info_dir = readdir(command_dir);
	}
	return (NULL);
}

static char	*find_command(char *cmd, char *path)
{
	DIR		*command_dir;
	char	*result;

	command_dir = opendir(path);
	if (!command_dir)
		return (NULL);
	result = search_in_dir(command_dir, cmd, path);
	closedir(command_dir);
	return (result);
}

char	**save_paths(void)
{
	char	*path_str;
	char	**path_list;

	path_str = getenv("PATH");
	if (!path_str)
		return (NULL);
	path_list = ft_split(path_str, ':');
	return (path_list);
}

static int	check_and_wait_for_pid(pid_t pid)
{
	int	status;

	status = 0;
	if (pid < 0)
	{
		ft_putstr_fd("failed process fork", STDOUT_FILENO);
		status = -1;
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	return (status);
}

static pid_t	fork_and_get_pid(int *status)
{
	pid_t	pid;

	pid = fork();
	*status = check_and_wait_for_pid(pid);
	return (pid);
}

int	call_external_command(char **command, t_shell *shell)
{
	char	*full_path;
	char	**path_list;
	size_t	i;
	int		status;

	status = 0;
	if (!fork_and_get_pid(&status))
	{
		path_list = save_paths();
		if (!path_list)
			return (-1);
		i = 0;
		while (path_list[i])
		{
			full_path = find_command(command[0], path_list[i]);
			if (full_path)
				execve(full_path, command, shell->envp);
			else
				execve(command[0], command, shell->envp);
			i++;
		}
		ft_putstr_fd("command not found\n", d_err);
		exit(127);
	}
	return (status);
}
