#include "../includes/minishell.h"

static int free_cd(char *oldpwd)
{
	free(oldpwd);
	return (1);
}

int	cd(const char *path, t_shell *shell)
{
	char *oldpwd;
	char *result;

	if (!path)
	{
		path = getenv("HOME");
		if (!path)
			return (free_cd(NULL));
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (chdir(path))
	{
		perror("cd");
		//printf("cd: %s: No such file or directory\n", path);
		return (free_cd(oldpwd));
	}
	result = ft_strjoin("OLDPWD=", oldpwd);
	if (!result)
		return (free_cd(oldpwd));
	set_var(result, &shell->envp);
	free(oldpwd);
	free(result);
	return (0);
}

int	pwd(void)
{
	char *cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	echo(char **command)
{
	size_t	i;

	if (!command[1])
	{
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(command[1], "-n", 3))
		i = 2;
	else
		i = 1;
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(command[1], "-n", 3))
		printf("\n");
	return (0);
}
int ms_exit(char **cmd, t_shell *sh)
{
		int	status;
		int	i;

		i = 0;
		printf("exit\n");
		if(cmd[1] && cmd[2])
			return (ms_err("exit: too many arguments\n", 2, d_err, sh));
		if (cmd[1])
		{
			if(cmd[1][i] == '+')
				i++;
			while(cmd[1][i] && (ft_isdigit(cmd[1][i]) != 0))
				i++;
			if(cmd[1][i] == '\0')
			{
				status = ft_atoi(cmd[1]);
			}
			else
				return (ms_err(" numeric argument required", 2, d_err, sh));
		}
		else
			status = sh->status_code;
		clean_minishell(sh);
		exit(status);
}
