#include "../includes/minishell.h"

static char *find_command2(DIR *command_dir, char *cmd, char *path)
{
    char *full_path;
    char *temp;
    struct dirent *info_dir;

    info_dir = readdir(command_dir);
    while(info_dir)
    {
        if (ft_strlen(cmd) != ft_strlen(info_dir->d_name))
        {
            info_dir = readdir(command_dir);
            continue ;
        }
        if(!ft_strncmp(cmd, info_dir->d_name, ft_strlen(cmd)))
        {
            temp = ft_strjoin(path, "/");
            full_path = ft_strjoin(temp, cmd);
            free(temp);
            return (full_path);
        }
        info_dir = readdir(command_dir);
    }
    return (NULL);
}

static char *find_command(char *cmd, char *path)
{
    DIR *command_dir;
    char *result;

    command_dir = opendir(path);
    if(!command_dir)
        return (NULL);
    result = find_command2(command_dir, cmd, path);
    closedir(command_dir);
    return (result);
}

char    **save_paths(void)
{
    char    *path_str;
    char    **path_list;

    path_str = getenv("PATH");
    if(!path_str)
        return (NULL);
    path_list = ft_split(path_str, ':');
    /*if (!path_list)
        return (NULL);*/ // not needed
    return (path_list);
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


pid_t subprocess(void)
{
    pid_t   pid;

    pid = fork();
    if (!pid)
        return (0);
    check_process(pid);
    return (pid);
}

void call_external_command(char **command/*char *name, t_node *inp_node*/)
{
    char    *full_path;
    char    **path_list;
    size_t  i;

    if (!subprocess())
    {
        path_list = save_paths();
        if(!path_list)
            return ;
        i = 0;
        while(path_list[i])
        {
            full_path = find_command(command[0], path_list[i]);
            if(full_path)
            {
                char *envp[] = {NULL}; //TODO
                execve(full_path, command, envp);
                exit (1);
            }
            i++;
        }
        ft_printf("%s: command not found\n", command[0]);
    }
}


