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

char	**save_paths(t_shell *shell)
{
	char	*path_str;
	char	**path_list;

	path_str = get_var("PATH", shell->envp);
	if (!path_str)
		return (NULL);
	path_list = ft_split(path_str, ':');
	free(path_str);
	return (path_list);
}

static void	call_ext_cmd_rel_path(char **path_list, char **cmd, t_shell *shell)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		full_path = find_command(cmd[0], path_list[i]);
		if (full_path)
			execve(full_path, cmd, shell->envp);
		i++;
	}
}

int	call_external_command(char **command, t_shell *shell)
{
	char	**path_list;
	int		status;

	status = 0;
	if (!fork_and_get_pid(&status))
	{
		path_list = save_paths(shell);
		if (!path_list)
			return (-1);
		call_ext_cmd_rel_path(path_list, command, shell);
		execve(command[0], command, shell->envp);
		free_arr(path_list);
		ft_putstr_fd("command not found\n", D_ERR);
		clean_minishell(shell);
		exit(127);
	}
	return (status);
}
