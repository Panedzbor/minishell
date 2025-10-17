#include "../includes/minishell.h"

static char	*join_new_line(char **old_input, char **new_line)
{
	char	*dupl;
	char	*nl_added;
	char	*new_input;

	if (!(*new_line))
		return (NULL);
	new_input = NULL;
	dupl = ms_strdup(*new_line);
	nl_added = ms_strjoin(dupl, "\n");
	if (*old_input)
		new_input = ms_strjoin(*old_input, nl_added);
	else
		new_input = ms_strdup(nl_added);
	free_and_reset_ptrs(2, (void **)old_input, (void **)new_line);
	free_and_reset_ptrs(2, (void **)&dupl, (void **)&nl_added);
	return (new_input);
}

static char	*create_heredoc_filename(void)
{
	static unsigned int	counter;
	char				*counter_str;
	char				*filename;

	counter++;
	counter_str = ft_itoa(counter);
	if (!counter_str)
		return (NULL);
	filename = ms_strjoin(D_HEREDOC_FILE, counter_str);
	free(counter_str);
	if (!filename)
		return (NULL);
	return (filename);
}

static char	*save_input_to_file(char *input)
{
	int		fd;
	char	*filename;

	filename = create_heredoc_filename();
	if (!filename)
		return (NULL);
	fd = open_file(filename, O_RDWR | O_CREAT | O_TRUNC);
	if (input)
		ft_putstr_fd(input, fd);
	close_file(fd);
	return (filename);
}

char	*run_here_doc(char *stop_str_with_quotes, t_shell *shell)
{
	char	*stop_str;
	int		quoted;
	char	*input_str;
	char	*new_line;
	char	*heredoc_file;

	save_current_streams(shell);
	set_streams(shell, 'd');
	new_line = NULL;
	input_str = NULL;
	quoted = 0;
	stop_str = trim_quotes(stop_str_with_quotes, &quoted);
	while (!same_string(new_line, stop_str))
	{
		input_str = join_new_line(&input_str, &new_line);
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
