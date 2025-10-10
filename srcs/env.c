#include "../includes/minishell.h"

static void add_var(char *var_input, t_shell *shell)
{
	set_var(var_input, &shell->local_vars);
	set_var(var_input, &shell->envp);
}

int env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int unset(char *var_name, t_shell *shell)
{
	delete_var(var_name, &shell->local_vars);
	delete_var(var_name, &shell->envp);
	return (0);
}

int export(char *var_input, t_shell *shell)
{
	int	i;
	char	*var;

	if (ft_strchr(var_input, '='))
		add_var(var_input, shell);
	else
	{
		i = search_var(var_input, shell->local_vars);
		if (i >= 0)
		{
			var = shell->local_vars[i];
			set_var(var, &shell->envp);
		}
		else
		{
			var = ft_strjoin(var_input, "=");
			if(!var)
				return (1);
			add_var(var, shell);
			free(var);
		}
	}
	return (0);
}
