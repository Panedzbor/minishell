#include "../includes/minishell.h"

static char *remove_quotes(char *str)
{
	char *result;
	int i;
	int j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		else
		{
			result[j] = str[i];
			i++;
			j++;
		}
	}
	result[j] = '\0';
	return (result);
}
static void	remove_quotes_from_argv(char **argv)
{
	int	i;
	char	*new_arg;

	i = 0;
	while (argv[i])
	{
		new_arg = remove_quotes(argv[i]);
		if (new_arg)
		{
			free(argv[i]);
			argv[i] = new_arg;
		}
		i++;
	}
}
static int validate_command(t_tree_node *node, t_shell *shell)
{
	int status;
	char **cmd;

	cmd = node->argv;
	remove_quotes_from_argv(node->argv);
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
		status = env(shell->envp);
	else if (!ft_strncmp(cmd[0], "exit", 5))
	{
		status = printf("Exit\n");
		clean_minishell(shell);
		exit(1);
	}
	else
		status = call_external_command(cmd, shell);
	return (status);
}

static int execute_logic_operator(t_tree_node *node, t_shell *shell, int sub_pipe)
{
	int status;

	status = execute_command_line(node->left, shell, sub_pipe, 0 /*?*/);
	if (status == 0 && node->type == NODE_AND)
		status = execute_command_line(node->right, shell, sub_pipe, 0);
	else if (status != 0 && node->type == NODE_OR)
		status = execute_command_line(node->right, shell, sub_pipe, 0);
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

int execute_command_line(t_tree_node *node, t_shell *shell, int sub_pipe, int streams)
{
	int status;

	status = 0;
	if (node->type == NODE_COMMAND)
		status = validate_command(node, shell);
	else if (node->type == NODE_PIPE)
		status = execute_pipe(node, shell, sub_pipe);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		status = execute_logic_operator(node, shell, sub_pipe);
	else if (node->type == NODE_REDIRECT_IN || node->type == NODE_REDIRECT_HERE_DOC || node->type == NODE_REDIRECT_OUT || node->type == NODE_REDIRECT_OUT_APPEND)
		status = execute_redirection(node, shell, streams);
	return (status);
}
