#include "minishell.h"

void    cd(const char *path)
{
    if (!path)
        path = getenv("HOME");
    if (chdir(path))
        printf("cd: %s: No such file or directory\n", path);
}


char *pwd(void)
{
    char *buf;
    size_t size;

    buf = NULL;
    size = 100;
    return(getcwd(buf, size));
}


