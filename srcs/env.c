#include "../includes/minishell.h"

void    env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
}

char *get_var_value(char *var_name, t_shell *shell)
{
    size_t i;
    size_t var_len;
    char * variable;
    size_t len;
    
    variable = ft_strjoin(var_name, "=");
    var_len = ft_strlen(variable);
    i = 0;
    while(shell->local_vars[i])
    {
        if (ft_strncmp(variable, shell->local_vars[i], var_len) == 0)
        {
            len = ft_strlen(shell->local_vars[i]) - var_len;
            return(ft_substr(shell->local_vars[i], var_len, len));
        }
        i++;
    }
    return (NULL);
}


