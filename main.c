#include "includes/minishell.h"

static char **ft_copy_envp(char **envp)
{
	int count = 0;
    char **result;
    int i;

	while (envp[count])
        count++;
	result = malloc((count + 1) * sizeof(char *));
    if (!result)
        return (NULL);
	 i = 0;
    while (i < count)
    {
        result[i] = ft_strdup(envp[i]);
		i++;
	}
	result[count] = NULL;
    return (result);
}

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell shell;
	t_tree_node *tree;

	(void)argc;
	(void)argv;
	shell.envp = ft_copy_envp(envp);
	shell.local_vars = NULL;
	while (1)
	{
		input = readline("Minishell: ");
		add_history((const char*)input);
		if (!input)
			continue ;
		tree = parser(input);
		//draw_tree(tree);
		execute_command_line(tree, &shell);
		test_print_shell_vars(&shell);
	}
	return (0);
}
