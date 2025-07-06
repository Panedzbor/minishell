#include "../includes/minishell.h"

extern char **environ;

void    env(void)
{
    int i;

    i = 0;
    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
}

char *seach_env_var(char *var_name)
{
    size_t i;
    size_t var_len;
    char * variable;
    size_t len;
    
    variable = ft_strjoin(var_name, "=");
    var_len = ft_strlen(variable);
    i = 0;
    while(environ[i])
    {
        if (ft_strncmp(variable, environ[i], var_len) == 0)
        {
            len = ft_strlen(environ[i]) - var_len;
            ft_printf("environ : %s\n", environ[i]);
            ft_printf("OUR PATH : %s\n", ft_substr(environ[i], var_len, len));
            return(ft_substr(environ[i], var_len, len));

        }
        i++;
    }
    return (NULL);
}

