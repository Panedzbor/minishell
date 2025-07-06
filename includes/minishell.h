#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "get_next_line.h"
# include <unistd.h>
# include <fcntl.h>


typedef struct s_node
{
    char* data;
    struct s_node* next;
} node;

node *create_node(char *data);
void	add_node(node **head, char* data);
void validate_command(node* node);
node	*split_to_nodes(char *str, char delimiter);
void    env(void);
char *seach_env_var(char *var_name);


//test
void test_list_data(node *test_node);
#endif
