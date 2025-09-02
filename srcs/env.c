#include "../includes/minishell.h"

void env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void unset(char *var_name, t_shell *shell)
{
	delete_var(var_name, &shell->local_vars);
	delete_var(var_name, &shell->envp);
}
void export(char *var_input, t_shell *shell)
{
	int i;
	char *checker;
	char *var;

	if (ft_strchr(var_input, '='))
	{
		set_var(var_input, &shell->local_vars);
		set_var(var_input, &shell->envp);
	}
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
			set_var(var, &shell->local_vars);
			set_var(var, &shell->envp);
			free(var);
		}
	}
}
