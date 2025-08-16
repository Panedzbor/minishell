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

//delete
typedef struct s_node
{
    char **command;
    struct s_node *next;
} t_node;
//delete

typedef enum e_type_node
{
	NODE_AND,
	NODE_COMMAND,
	NODE_OR,
	NODE_PIPE,
	NODE_REDIRECT_IN,		  //<
	NODE_REDIRECT_IN_MANUAL,  //<<
	NODE_REDIRECT_OUT,		  //>
	NODE_REDIRECT_OUT_APPEND, //>>
	NODE_SUBSHELL
} t_type_node;

typedef enum e_token_type
{
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PAREN_LEFT,
	TOKEN_PAREN_RIGH,
	TOKEN_PIPE,
	TOKEN_QUOTE,
	TOKEN_QUOTE_DBL,
	TOKEN_REDIRECT_IN,		  //<
	TOKEN_REDIRECT_IN_MANUAL,  //<<
	TOKEN_REDIRECT_OUT,		  //>
	TOKEN_REDIRECT_OUT_APPEND,
	TOKEN_WORD
}t_token_type;

typedef struct s_token
{
	char *value;
	t_token_type token_type;
	struct s_token *next;
	struct s_token *prev;
} t_token;

typedef struct s_tree_node
{
	t_type_node type;
	char **argv;
	char *file_name;
	struct s_tree_node *left;
	struct s_tree_node *right;
} t_tree_node;

t_node    *create_node(char *command);
int		is_symbol_oper(char с);
void	add_token(t_token **head, char *value, t_token_type type);
void	add_node_to_list(t_node **head, char* command);
t_token *lexer(char *input);
void	tokenize_operator(char **str, t_token **token_list);
void    validate_command(t_node* node);
t_node	*create_cmd_list(char **data);
void    env(void);
char    *seach_env_var(char *var_name);
void    call_external_command(char **command);
void    cd(const char *path);
char    *pwd(void);
void    echo(char **command);
void    check_process(pid_t pid);
int     check_operator(char *token);
char    **split_input(char *input);

//test
void    test_list_data(t_node *test_node);
void	print_tokens(t_token *head);
#endif
