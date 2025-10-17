#include "includes/minishell.h"

volatile sig_atomic_t	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	set_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (process_input(&input, &shell))
			continue ;
		add_history((const char *)input);
		if (parser(input, &shell))
			continue ;
		free(input);
		if (!collect_heredocs(shell.tree, &shell))
			continue ;
		shell.status_code = execute_command_line(shell.tree, &shell, 0, 0);
		clean_session(&shell);
		reset_streams(shell);
	}
	return (0);
}
