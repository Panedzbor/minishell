#include "../includes/minishell.h"

static char *trim_quotes(char *str, int *quoted)
{
	size_t len;

	len = ft_strlen(str);
	if (len > 1)
	{
		if ((str[0] == '\"' && str[len - 1] == '\"')
			|| (str[0] == '\'' && str[len - 1] == '\''))
		{
			*quoted = 1;
			return (ft_substr(str, 1, len - 2));
		}
	}
	return (ft_strdup(str));
}

static void check_ptr(void *ptr)
{
	if (!ptr)
		return ; //run error handler
}

static char *ms_strjoin(const char *s1, const char *s2)
{
	char *result;

	result = ft_strjoin(s1, s2);
	check_ptr(result);
	return (result);
}

static char *ms_strdup(const char *str)
{
	char *result;

	result = ft_strdup(str);
	check_ptr(result);
	return (result);
}

static char *expand_new_line(char *nl, int quoted)
{
	char *expanded;

	if (!quoted)
	{
		//expanded = # var expansion func #;
		expanded = ms_strdup(nl); //temporary
	}
	else
		expanded = ms_strdup(nl);
	return (expanded);
}

static char *join_new_line(char **old_input, char **new_line, int quoted)
{
	char *expanded;
	char *nl_added;
	char *new_input;

	if (!(*new_line))
		return (NULL);
	new_input = NULL;
	expanded = expand_new_line(*new_line, quoted);
	nl_added = ms_strjoin(expanded, "\n");
	if (*old_input)
		new_input = ms_strjoin(*old_input, nl_added);
	else
		new_input = ms_strdup(nl_added);
	free_and_reset_ptrs(2, (void **)old_input, (void **)new_line);
	free_and_reset_ptrs(2, (void **)&expanded, (void **)&nl_added);
	return (new_input);
}

static char *create_heredoc_filename(void)
{
	static unsigned int counter;
	char *counter_str;

	counter++;
	counter_str = ft_itoa(counter);
	check_ptr(counter_str);
	return (ms_strjoin(d_heredoc_file, counter_str));
}

static char *save_input_to_file(char *input)
{
	int fd;
	char *filename;
	
	filename = create_heredoc_filename();
	fd = open_file(filename, O_RDWR | O_CREAT | O_TRUNC);
	if (input)
		ft_putstr_fd(input, fd);
	close_file(fd);
	return (filename);
}

void save_current_streams(t_shell *shell)
{
    shell->cur_input_stream = dup(STDIN_FILENO);
	shell->cur_output_stream = dup(STDOUT_FILENO);
    if (isatty(STDIN_FILENO))
    	tcgetattr(STDIN_FILENO, &shell->cur_attributes);
}

static void close_streams(t_shell *shell, char option)
{
    if (option == 'd')
    {
        close(shell->def_input_stream);
        close(shell->def_output_stream);
    }
    else if(option == 'c')
    {
        close(shell->cur_input_stream);
        close(shell->cur_output_stream);
    }
}

static void set_streams(t_shell *shell, char option)
{
    if (option == 'd')
    {
        dup2(shell->def_input_stream, STDIN_FILENO);
        dup2(shell->def_output_stream, STDOUT_FILENO);
    }
    else if (option == 'c')
    {
        dup2(shell->cur_input_stream, STDIN_FILENO);
        dup2(shell->cur_output_stream, STDOUT_FILENO);
        close_streams(shell, 'c');
    }
}

char *run_here_doc(char *stop_str_with_quotes, t_shell *shell)
{
	char *stop_str;
	int	quoted;
	char *input_str;
	char *new_line;
	char *heredoc_file;

    save_current_streams(shell);
    set_streams(shell, 'd');
	new_line = NULL;
	input_str = NULL;
	quoted = 0;
	stop_str = trim_quotes(stop_str_with_quotes, &quoted);
	while (!same_string(new_line, stop_str))
	{
		input_str = join_new_line(&input_str, &new_line, quoted);
		new_line = readline("> ");
		if (!new_line)
			break ;
	}
	free_and_reset_ptrs(2, (void **)&new_line, (void **)&stop_str);
	heredoc_file = save_input_to_file(input_str);
	free_and_reset_ptrs(1, (void **)&input_str);
    set_streams(shell, 'c');
	return (heredoc_file);
}
