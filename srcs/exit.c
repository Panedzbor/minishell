#include "../includes/minishell.h"

int	ms_exit(char **cmd, t_shell *sh)
{
	int	status;
	int	i;

	i = 0;
	printf("exit\n");
	if (cmd[1] && cmd[2])
		return (ms_err("exit: too many arguments\n", 2, D_ERR, sh));
	if (cmd[1])
	{
		if (cmd[1][0] == '+' || cmd[1][0] == '-')
			i++;
		while (cmd[1][i] && (ft_isdigit(cmd[1][i]) != 0))
			i++;
		if (cmd[1][i] == '\0')
			status = ft_atoi(cmd[1]);
		else
			return (ms_err(" numeric argument required", 2, D_ERR, sh));
	}
	else
		status = sh->status_code;
	clean_minishell(sh);
	exit(status);
}
