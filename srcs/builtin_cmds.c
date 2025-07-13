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

void echo(t_node *node)
{
	bool newline;

	newline = true;
	if (node->next == NULL)
	{
		printf("\n");
		return;
	}
	if (!ft_strncmp(node->next->data, "-n", 3))
	{
		if (node->next->next == NULL)
			return ;
		node = node->next->next;
		newline = false;
	}
	else
		node = node->next;
	while (node->next)
	{
		printf("%s ", node->data);
		node = node->next;
	}
	printf("%s", node->data);
	if (newline)
		printf("\n");
}
