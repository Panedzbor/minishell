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

static char *join_new_line(char **old_input, char **new_line, int quoted)
{
	char *temp;
	char *new_input;

	temp = NULL;
	new_input = NULL;
	if (!quoted)
	{
		// run variable expansion on new line;
	}
	if (*old_input)
		temp = ft_strjoin(*old_input, "\n");
	if (!temp && *old_input)
		return (NULL); //run error handler here
	if (temp)
		new_input = ft_strjoin(temp, *new_line);
	else if (*new_line)
		new_input = ft_strdup(*new_line);
	if (!new_input && *new_line)
		return (NULL); //run error handler here
	free_and_reset_ptrs(3, 
						(void **)old_input, (void **)new_line, (void **)&temp);
	return (new_input);
}

static void save_input_to_file(char *input)
{
	int fd;

	if (!input)
		return ;
	fd = open_file(heredoc_file, O_RDWR | O_CREAT | O_TRUNC);
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
	close_file(fd);
}

void run_here_doc(char *stop_str_with_quotes, t_shell shell)
{
	char *stop_str;
	int	quoted;
	char *input;
	char *new_line;
    int target_fd;

	new_line = NULL;
	input = NULL;
	quoted = 0;
    target_fd = dup(STDIN_FILENO);
    dup2(shell.default_input_stream, STDIN_FILENO);
	stop_str = trim_quotes(stop_str_with_quotes, &quoted);
	while (!same_string(new_line, stop_str))
	{
		input = join_new_line(&input, &new_line, quoted);
		new_line = readline("> ");
	}
	free_and_reset_ptrs(1, (void **)&new_line);
	save_input_to_file(input);
	free_and_reset_ptrs(1, (void **)&input);
    dup2(target_fd, STDIN_FILENO);
}
