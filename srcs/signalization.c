#include "../includes/minishell.h"

static void	save_sig(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	set_signals(void)
{
	signal(SIGINT, save_sig);
	signal(SIGQUIT, SIG_IGN);
}
static char	*trim(char *str)
{
	char	*start;
	char	*end;

	if(!str)
		return(NULL);
	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	if(*start == '\0')
	{
	*str = '\0';
	return (str);
	}
	end = start + (ft_strlen(start) - 1);
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	return (start);
}

int	process_input(char **input, t_shell *shell)
{
	char	*trim_input;

	if (!(*input))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		clean_minishell(shell);
		exit(shell->status_code);
	}
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		free(*input);
		return (1);
	}
	trim_input = trim(*input);
	if (same_string(trim_input, ""))
	{
		free(*input);
		return (1);
	}
	return (0);
}
