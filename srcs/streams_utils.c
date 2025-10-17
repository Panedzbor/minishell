#include "../includes/minishell.h"

void	close_streams(t_shell *shell, char option)
{
	if (option == 'd')
	{
		close(shell->def_input_stream);
		close(shell->def_output_stream);
	}
	else if (option == 'c')
	{
		close(shell->cur_input_stream);
		close(shell->cur_output_stream);
	}
}

void	set_streams(t_shell *shell, char option)
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
