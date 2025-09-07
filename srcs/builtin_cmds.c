#include "minishell.h"

int cd(const char *path, t_shell *shell)
{
	char *oldpwd;
	char *result;
	
	if (!path)
		path = getenv("HOME");
	oldpwd = getcwd(NULL, 0);	
	if (chdir(path))
	{
		printf("cd: %s: No such file or directory\n", path);
		free(oldpwd);
		return (1);
	}
	result= ft_strjoin("OLDPWD=",oldpwd);
	set_var(result, &shell->envp);
	return (0);
}

int pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int echo(char **command) // TODO: 1) echo "omg bro"
{
	size_t i;

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
		if(command[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(command[1], "-n", 3))
		printf("\n");
	return (0);
}
