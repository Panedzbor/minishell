#include "../includes/minishell.h"

static int	check_valid_name(char *name)
{
	int	i;

	i = 0;
	if (name[0] == '=' || ft_isdigit(name[0]))
		return (0);
	while (name[i] != '=' && name[i])
	{
		if (valid_var_char(name[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	env(char **envp)
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

int	unset(char *var_name, t_shell *shell)
{
	if (!var_name)
		return (0);
	delete_var(var_name, &shell->local_vars);
	delete_var(var_name, &shell->envp);
	return (0);
}
static int	export_no_equal(char *var_input, t_shell *shell)
{
	int		i;
    char	*var;

    i = search_var(var_input, shell->local_vars);
    if (i >= 0)
    {
        var = shell->local_vars[i];
        set_var(var, &shell->envp);
    }
    else
    {
        var = ft_strjoin(var_input, "=");
        if (!var)
            return (1);
        set_var(var_input, &shell->local_vars);
        set_var(var_input, &shell->envp);
        free(var);
    }
    return (0);
}

int	export(char *var_input, t_shell *shell)
{
	if(!var_input)
		return (env(shell->envp));
	if (!check_valid_name(var_input))
		return (ms_err(" not a valid identifier", 1, d_err, shell));
	if (ft_strchr(var_input, '='))
	{
		set_var(var_input, &shell->local_vars);
		set_var(var_input, &shell->envp);
	}
	else
		return (export_no_equal(var_input, shell));
	return (0);
}
