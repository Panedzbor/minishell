#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>

typedef struct s_node
{
    char* data;
    struct s_node* next;
} node;

node *create_node(char *data);
void validate_command(node* node);

#endif
