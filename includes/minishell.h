#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define D_HEREDOC_FILE "./tmp/here_doc_input"
# define D_ERR STDERR_FILENO

extern volatile sig_atomic_t	g_sig;

typedef struct termios			t_attr;

typedef enum e_token_type
{
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PAREN_LEFT,
	TOKEN_PAREN_RIGH,
	TOKEN_PIPE,
	TOKEN_QUOTE,
	TOKEN_QUOTE_DBL,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_HERE_DOC,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_OUT_APPEND,
	TOKEN_WORD,
	TOKEN_END_OF_LIST
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	token_type;
	size_t			priority;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_node_type
{
	NODE_AND,
	NODE_COMMAND,
	NODE_FILENAME,
	NODE_OR,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_HERE_DOC,
	NODE_REDIR_OUT,
	NODE_REDIR_OUT_APPEND,
	NODE_SUBSHELL
}	t_node_type;

typedef struct s_priorities
{
	t_token_type	type[11];
	int				value[11];
}	t_priora;

typedef struct s_tree_node
{
	t_node_type			type;
	char				**argv;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_shell
{
	char		**envp;
	char		**local_vars;
	t_token		*tokens;
	t_tree_node	*tree;
	int			def_input_stream;
	int			def_output_stream;
	t_attr		def_attributes;
	int			cur_input_stream;
	int			cur_output_stream;
	t_attr		cur_attributes;
	int			status_code;
}	t_shell;

void		add_token(t_token **head, char *value, 
				t_token_type type, t_priora prior_map);
t_token		*analyze_parenthesis(t_token *tokens, int parenth_open);
size_t		calc_res_len(char *str, t_shell *shell);
int			call_external_command(char **command, t_shell *shell);
int			cd(const char *path, t_shell *shell);
void		*check_alloc(void *ptr);
int			check_operator(char *token);
void		check_ptr(void *ptr);
void		clean_minishell(t_shell *shell);
void		clean_session(t_shell *shell);
void		close_file(int fd);
void		close_streams(t_shell *shell, char option);
void		*collect_heredocs(t_tree_node *node, t_shell *shell);
pid_t		create_subprocess(void);
t_tree_node	*create_tree_node(t_token *token);
void		delete_var(char *var_name, char ***var_store);
t_token		*divide_tokens(t_token *start, t_token *end, 
				t_token **left, t_token **right);
int			echo(char **command);
int			env(char **envp);
int			execute_command_line(t_tree_node *node, t_shell *shell, 
				int sub_pipe, int streams);
int			execute_pipe(t_tree_node *node, t_shell *shell, int sub_pipe);
int			execute_redirection(t_tree_node *node, t_shell *shell, int streams);
char		**extend_arr( char *ext_str, char **arr);
void		expand_tokens(t_token *token_list, t_shell *shell);
char		*expand_variables(char *str, t_shell *shell);
int			export(char *var_input, t_shell *shell);
t_token		*find_lowest_priority(t_token *start, t_token *end);
pid_t		fork_and_get_pid(int *status);
void		free_arr(char **arr);
void		free_and_reset_ptrs(int amount, void **ptr, ...);
int			ft_arr_el_count(void **arr);
char		**ft_charrdup(char **arr);
char		*get_exp_var_nam(char *str, int pos, size_t *name_len);
char		*get_exp_var_val(char *var_name, t_shell *shell);
int			get_info_about_stream(int info_about_streams, char stream);
int			get_token_priority(t_token_type type, t_priora priority_map);
char		*get_var(char *var_name, char **var_store);
char		*get_exp_var_val(char *var_name, t_shell *shell);
void		init_shell(t_shell *shell, char **envp);
void		init_token_priority(t_priora *prior);
void		is_token_seq(t_token **priora, t_token **priora_end, 
				t_token_type cur_token_type);
int			is_symbol_oper(char c);
int			lexer(char *input, t_shell *shell);
int			ms_cd(char **cmd, t_shell *shell);
int			ms_err(char *err_message, int status, int fd, t_shell *shell);
int			ms_exit(char **cmd, t_shell *shell);
int			ms_ex_err(char *err_message, int status, int fd, t_shell *shell);
char		*ms_strdup(const char *str);
char		*ms_strjoin(const char *s1, const char *s2);
int			open_file(char *filename, int flags);
void		overwrite_stream(char stream, int *info, int new_fd);
int			parser(char *input, t_shell *shell);
int			process_input(char **input, t_shell *shell);
int			pwd(void);
void		remove_quotes_from_argv(char **argv);
void		reset_streams(t_shell shell);
int			run_cmd_in_cur_proc(int fd_to_duplicate, int fd[2], 
				t_tree_node *node, t_shell *shell);
char		*run_here_doc(char *stop_str_with_quotes, t_shell *shell);
int			same_string(char *str1, char *str2);
void		save_current_streams(t_shell *shell);
int			search_var(char *var_name, char **var_store);
void		set_signals(void);
void		set_streams(t_shell *shell, char option);
void		set_var(char *var_name, char ***var_store);
char		**shorten_arr(char *del_str, char **arr);
int			tokenize_oper(char **str, t_token **token_list, t_priora prior_map);
char		*trim_quotes(char *str, int *quoted);
int			unset(char *var_name, t_shell *shell);
int			valid_token_order(t_token *list);
int			valid_var_char(char c);
void		wait_for_subprocess(pid_t pid);

#endif
