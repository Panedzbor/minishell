#include "../includes/minishell.h"

int	ms_err(char *err_message, int status, int fd, t_shell *shell)
{
	if (err_message)
		ft_putstr_fd(err_message, fd);
	clean_session(shell);
	return (status);
}

int	ms_ext_err(char *err_message, int status, int fd, t_shell *shell)
{
	if (err_message)
		ft_putstr_fd(err_message, fd);
	clean_minishell(shell);
	return (status);
}