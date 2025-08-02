#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>


typedef struct s_node
{
    char* data;
    struct s_node* next;
} t_node;

t_node    *create_node(char *data);
void	add_node(t_node **head, char* data);
void    validate_command(t_node* node);
t_node	*split_to_nodes(char *str, char delimiter);
void    env(void);
char    *seach_env_var(char *var_name);
void    call_external_command(char *name);
void    cd(const char *path);
char *pwd(void);
void echo(t_node *node);
void check_process(pid_t pid);
int	check_operator(char *token);

//test
void    test_list_data(t_node *test_node);
#endif
