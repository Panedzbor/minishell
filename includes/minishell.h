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

typedef enum e_node_type
{
	NODE_AND,
	NODE_COMMAND,
	NODE_OR,
	NODE_PIPE,
	NODE_REDIRECT_IN,		  //<
	NODE_REDIRECT_IN_MANUAL,  //<<
	NODE_REDIRECT_OUT,		  //>
	NODE_REDIRECT_OUT_APPEND, //>>
	NODE_SUBSHELL,
	NODE_WORDS
} t_node_type;

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
	TOKEN_WORD,
	TOKEN_END_OF_LIST
} t_token_type;

typedef struct s_token
{
	char *value;
	t_token_type token_type;
	size_t priority;
	struct s_token *next;
	struct s_token *prev;
} t_token;

typedef struct s_tree_node
{
	t_node_type type;
	char **argv;
	//char *file_name;
	struct s_tree_node *left;
	struct s_tree_node *right;
} t_tree_node;

typedef struct s_priorities
{
	t_token_type type[11];
	int	value[11];
} t_priora;

t_node    *create_node(char *command);
int		is_symbol_oper(char с);
void	add_token(t_token **head, char *value, t_token_type type, t_priora priority_map);
void	add_node_to_list(t_node **head, char* command);
t_token *lexer(char *input);
void	tokenize_operator(char **str, t_token **token_list, t_priora priority_map);
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
t_tree_node *fill_tree(t_token *start, t_token *end);
t_token *divide_input(t_token *start, t_token *end, t_token **left, t_token **right);
t_token *find_lowest_priority(t_token *start, t_token *end);
t_tree_node *create_tree_node(t_token *token);
void init_prior(t_priora *prior);
int get_token_priority(t_token_type type, t_priora priority_map);
t_token *analyze_parenthesis(t_token *tokens, int parenth_open);
t_token *check_closed_parenths(t_token *last, int parenth_open);
t_token *find_list_end(t_token *start);
t_node_type define_node_type(t_token_type tt);
t_token *subshell_trim(t_token *start, t_token *end, t_token **left);
void check_if_word_sequence(t_token **priora, t_token **priora_end);
void assign_value_to_argv(t_tree_node *node, t_token *token);

//test
void    test_list_data(t_node *test_node);
void	print_tokens(t_token *head);
void    test_anal_parent(t_token *token);
void draw_tree(t_tree_node *tree);
void save_nodes(t_tree_node *tree, int target_level, int current_level, t_tree_node **print_arr, int *index);
char *get_symbol(t_tree_node *node);
int count_tree_depth(t_tree_node *node, int curlevel);

#endif
