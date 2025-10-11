#include "includes/minishell.h"

sig_atomic_t g_sig;

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	signal(SIGINT, save_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (g_sig == SIGINT)
		{
			stop_exec();
		}

		printf("gsig %d/n", g_sig);

		input = readline("minishell: ");


		add_history((const char*)input);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (same_string(input, ""))
		{
			free(input);
			continue ;
		}
		parser(input, &shell);
		free(input);
		collect_heredocs(shell.tree, &shell);
		shell.status_code = execute_command_line(shell.tree, &shell, 0, 0);
		clean_session(&shell);
		reset_streams(shell);
	}
	return (0);
}

