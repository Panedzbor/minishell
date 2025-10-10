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
		printf("cd: %s: No such file or directory\n", path);
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
