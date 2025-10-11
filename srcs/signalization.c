#include "../includes/minishell.h"

extern/* volatile */	sig_atomic_t g_sig;

void save_sig(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	stop_exec();
	g_sig = sig;
}

void stop_exec(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig = 0;
}

