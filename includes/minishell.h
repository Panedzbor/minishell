#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

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
	TOKEN_VAR_ASSIGN,
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
	NODE_VAR_ASSIGN
} t_node_type;

typedef struct s_priorities
{
	t_token_type type[12];
	int	value[12];
} t_priora;

typedef struct s_tree_node
{
	t_node_type type;
	char **argv;
	//char *file_name;
	struct s_tree_node *left;
	struct s_tree_node *right;
} t_tree_node;

typedef struct s_shell
{
	char		**envp;
	char		**local_vars;
} t_shell;

void		add_token(t_token **head, char *value, t_token_type type, t_priora priority_map);
t_token 	*analyze_parenthesis(t_token *tokens, int parenth_open);
int    		call_external_command(char **command, t_shell *shell);
int	    	cd(const char *path);
void		check_if_token_sequence(t_token **priora, t_token **priora_end, t_token_type cur_token_type);
int     	check_operator(char *token);
int	    	check_process(pid_t pid);
t_tree_node *create_tree_node(t_token *token);
void		delete_var(char *var_name, char **var_store);
t_token		*divide_tokens(t_token *start, t_token *end, t_token **left, t_token **right);
int	    	echo(char **command);
void    	env(char ** envp);
int			execute_command_line(t_tree_node *node, t_shell *shell);
char		**extend_arr( char *ext_str, char **arr);
void		export(char *var_input, t_shell *shell); //TODO change
t_token		*find_lowest_priority(t_token *start, t_token *end);
void		find_variable_assignments(t_token **token);
int			get_token_priority(t_token_type type, t_priora priority_map);
char		*get_var_value(char *var_name, t_shell *shell);
void		init_token_priority(t_priora *prior);
int			is_symbol_oper(char с);
t_token		*lexer(char *input);
t_tree_node *parser(char *input);
int			pwd(void);
char		*search_var(char *var_name, char **var_store);
void		set_var(char *var_name, char **var_store);
char		**shorten_arr(char **arr, char *del_str);
void		tokenize_operator(char **str, t_token **token_list, t_priora priority_map);
void		unset(char *var_name, t_shell *shell); //TODO change

//test
void    test_analyze_parent(t_token *token);
void	test_print_tokens(t_token *head);
void	test_print_shell_vars(t_shell *shell);
void 	draw_tree(t_tree_node *tree);

#endif
