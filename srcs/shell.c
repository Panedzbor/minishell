#include "../includes/minishell.h"

static char	**ft_copy_envp(char **envp)
{
	int		count;
	char	**result;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	result = (char **)ft_calloc((count + 1), sizeof(char *));
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

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = ft_copy_envp(envp);
	shell->local_vars = NULL;
	shell->tokens = NULL;
	shell->tree = NULL;
	shell->cur_input_stream = 0;
	shell->cur_output_stream = 0;
	shell->def_input_stream = dup(STDIN_FILENO);
	shell->def_output_stream = dup(STDOUT_FILENO);
	shell->status_code = 0;
	tcgetattr(STDIN_FILENO, &shell->def_attributes);
}
