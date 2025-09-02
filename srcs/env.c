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
	delete_var(var_name, shell->local_vars);
	delete_var(var_name, shell->envp);
}
void export(char *var_name, t_shell *shell)
{
	char *var;

	var = search_var(*var_name, shell->local_vars);
	if (var)
		set_var(var, shell->envp);	
}