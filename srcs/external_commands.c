#include "../includes/minishell.h"

static char *find_command(char *name, char *path)
{
    DIR *command_dir;
    struct dirent *info_dir;
    char *full_path;
    char *temp;

    command_dir = opendir(path);
    if(!command_dir)
        return (NULL);
    info_dir = readdir(command_dir);
    while(info_dir != NULL)
    {
        if (ft_strlen(name) != ft_strlen(info_dir->d_name))
            continue ;
        if(!ft_strncmp(name, info_dir->d_name, ft_strlen(name)))
        {
            temp = ft_strjoin(path, "/");
            free(temp);
            full_path = ft_strjoin(temp, name);
            return (full_path);
        }
        info_dir = readdir(command_dir);
    }
    return (NULL);
}

t_node    *save_paths(void)
{
    char    *path;
    t_node  *path_node;

    path = getenv("PATH");
    if(!path)
        return ;
    path_node = split_to_nodes(path, ':');
    return (path_node);
}

size_t  count_elements_for_argv(t_node *inp_node)
{
    size_t i;
    t_node  *next;

    i = 1;
    next = inp_node->next;
    while (next)
    {
        i++;
        next = inp_node->next;
    }
    return (i);
}

void assign_values_to_argv(t_node *inp_node, char **argv, size_t len_argv)
{
    *argv = ft_calloc(len_argv, sizeof(char *));
}

char **fill_process_argv(t_node *inp_node)
{
    char *argv;
    size_t len_argv;

    while(!check_operator(inp_node->data))
    {
        len_argv = count_elements_for_argv(inp_node);
        assign_values_to_argv(inp_node, &argv, len_argv);
    }
}

void call_external_command(char *name, t_node *inp_node)
{
    char    *result;
    t_node    *path_node;
    pid_t   pid;

    pid = fork();
    if (pid != 0)
        check_process(pid);
    else
    {
        path_node = save_paths();
        if(!path_node)
            return ;
        while(path_node)
        {
            result = find_command(name, path_node->data);
            if(result != NULL)
            {

                char *argv[] = {name, NULL};
                char *envp[] = {NULL}; //TODO
                execve(result, argv, envp);
                exit (1);
            }
            path_node = path_node->next;
        }
        ft_printf("%s: command not found\n", name);
    }
}
