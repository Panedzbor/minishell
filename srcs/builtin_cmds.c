#include "minishell.h"

void cd(const char *path)
{
	if (!path)
		path = getenv("HOME");
	if (chdir(path))
		printf("cd: %s: No such file or directory\n", path);
}

char *pwd(void)
{
	char *buf;
	size_t size;

	buf = NULL;
	size = 100;
	return (getcwd(buf, size));
}

void echo(char **command) // TODO: 1) echo "omg bro" 2) echo -n: remove space
{
	size_t i;

	if (!command[1])
	{
		printf("\n");
		return ;
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
}
