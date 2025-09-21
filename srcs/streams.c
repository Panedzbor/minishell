#include "../includes/minishell.h"

int get_info_about_stream(int info_about_streams, char stream)
{
	if (stream == 'I')
		return (info_about_streams >> 1);
	return (info_about_streams & 1);
}

void overwrite_stream(char stream, int *info, int new_fd)
{
	if (stream == 'I')
	{
		dup2(new_fd, STDIN_FILENO);
		*info += 2;
	}
	else
	{
		dup2(new_fd, STDOUT_FILENO);
		*info += 1;
	}
}

void reset_streams(t_shell shell)
{
	dup2(shell.def_input_stream, STDIN_FILENO);
	dup2(shell.def_output_stream, STDOUT_FILENO);
}