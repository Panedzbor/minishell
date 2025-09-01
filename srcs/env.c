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

void unset(char *var_name, t_shell *shell)
{
    char *local_str;
    char *env_str;
    
    local_str = search_var(var_name, shell->local_vars);
    if(local_str)
        shell->local_vars = 
    env_str = search_var(var_name, shell->envp);    
}