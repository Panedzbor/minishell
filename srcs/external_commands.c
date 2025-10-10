#include "../includes/minishell.h"


static char *search_in_dir(DIR *command_dir, char *cmd, char *path)
{
    //TODO : refactoring + free
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
    result = search_in_dir(command_dir, cmd, path);
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
    //free (path_str)
    /*if (!path_list)
        return (NULL);*/ // not needed
    return (path_list);
}

// size_t  count_elements_for_argv(t_node *inp_node)
// {
//     size_t i;
//     t_node  *next;

//     i = 1;
//     next = inp_node->next;
//     while (next)
//     {
//         i++;
//         next = inp_node->next;
//     }
//     return (i);
// }

static int check_and_wait_for_pid(pid_t pid)
{
	int status;

	status = 0;
	if (pid < 0)
	{
		printf("Fork failed\n");
		status = -1;
		//exit(1); //launch error handler here
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0); //maybe better to use like in pipe (wait_for_subprocess)
		status = WEXITSTATUS(status);
	}
	return (status);
}

static pid_t fork_and_get_pid(int *status)
{
    pid_t   pid;

    pid = fork();
    if (!pid)
        return (0);//лишнее действие?
    *status = check_and_wait_for_pid(pid);
    return (pid);
}

int call_external_command(char **command, t_shell *shell)
{
    char    *full_path;
    char    **path_list;
    size_t  i;
    int     status;
    
    status = 0;
    if (!fork_and_get_pid(&status))
    {
        path_list = save_paths();
        if(!path_list)
            return (-1);
        i = 0;
        while(path_list[i])
        {
            full_path = find_command(command[0], path_list[i]);
            if(full_path)
                execve(full_path, command, shell->envp);
            i++;
        }
        ft_printf("%s: command not found\n", command[0]);
        exit(127);
    }
    return (status);
}


