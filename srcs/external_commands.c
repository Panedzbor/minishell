#include "../includes/minishell.h"

static char *find_command(char *name, char *path)
{
    DIR *command_dir;
    struct dirent *info_dir;
    
    command_dir = opendir(path);
    if(!command_dir)
        return (NULL);
    info_dir = readdir(command_dir);
    while(info_dir != NULL)
    {
        if(!strcmp(name, info_dir->d_name))
        {
            return (info_dir->d_name);
        }
        info_dir = readdir(command_dir);
    }
    return (NULL);
}
void call_external_command(char *name)
{
    char    *result;
    node    *path_node;
    char    *path;

    path = getenv("PATH");
    if(!path)
    {
        return ;
    }
    path_node = split_to_nodes(path, ':');
    {
    if(!path_node)
        return ;
    }
    while(path_node)
    {
        result = find_command(name, path_node->data);
        if(result != NULL)
        {
            ft_printf("%s: command exist\n", name);
            return ;
        }
        path_node = path_node->next;
    }
    ft_printf("%s: command not found\n", name);
}
