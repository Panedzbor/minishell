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
	fd = open_file(d_heredoc_file, O_RDWR | O_CREAT | O_TRUNC);
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
	close_file(fd);
}

void save_current_streams(t_shell *shell)
{
    //shell->cur_input_stream = dup(STDIN_FILENO);
    dup2(STDIN_FILENO, shell->cur_input_stream);
	//shell->cur_output_stream = dup(STDOUT_FILENO);
    dup2(STDOUT_FILENO, shell->cur_output_stream);
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
    //int tty_fd;
    
    if (option == 'd')
    {
        dup2(shell->def_input_stream, STDIN_FILENO);
        //dup2(shell->def_output_stream, STDOUT_FILENO);
        tcsetattr(STDIN_FILENO, TCSANOW, &shell->def_attributes);
    }
    else if (option == 'c')
    {
        dup2(shell->cur_input_stream, STDIN_FILENO);
        //dup2(shell->cur_output_stream, STDOUT_FILENO);
        tcsetattr(STDIN_FILENO, TCSANOW, &shell->cur_attributes);
        //close_streams(shell, 'c');
    }
    // else if (option == 'n')
    // {
    //     tty_fd = open_file("/dev/tty", O_RDWR);
    //     dup2(tty_fd, STDIN_FILENO);

    // }
}

void run_here_doc(char *stop_str_with_quotes, t_shell *shell)
{
	char *stop_str;
	int	quoted;
	char *input_str;
	char *new_line;

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
	}
	free_and_reset_ptrs(1, (void **)&new_line);
	save_input_to_file(input_str);
	free_and_reset_ptrs(1, (void **)&input_str);
    set_streams(shell, 'c');
}
