#include "minishell.h"

int cd(const char *path)
{
	if (!path)
		path = getenv("HOME");
	if (chdir(path))
	{
		printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

int pwd(void)
{
	char *buf;
	size_t size;

	buf = NULL;
	size = 100;
	printf("%s\n", getcwd(buf, size));
	return (0);
}

int echo(char **command) // TODO: 1) echo "omg bro" 2) echo -n: remove space
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
		printf("%s ", command[i]);
		i++;
	}
	if (ft_strncmp(command[1], "-n", 3))
		printf("\n");
	return (0);
}
