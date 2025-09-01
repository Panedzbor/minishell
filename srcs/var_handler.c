#include "../includes/minishell.h"

static char *search_var(char *var_name, char **var_store)
{
    size_t i;
    size_t var_len;
    char * variable;

    variable = ft_strjoin(var_name, "=");
    var_len = ft_strlen(variable);
    while(var_store[i])
    {
     if (ft_strncmp(var_name, var_store[i], var_len) == 0)
        {
            return var_store[i];
        }
        i++;
    }
    return NULL;
}

char *get_var_value(char *var_name, char **var_store)
{
    size_t var_len;
    char * variable;
    size_t len;
    char *result;

    variable = ft_strjoin(var_name, "=");
    var_len = ft_strlen(var_name);
    result = search_var(var_name, var_store);
    if(result)
        {
            len = ft_strlen(result) - var_len;
            return(ft_substr(result, var_len, len));
        }
    return (NULL);
}
void set_var(char *var_name, char **var_store)
{
    char *result;    
    result = search_var(var_name, var_store);
             
}
