#include "includes/minishell.h"

int	main(void)
{
	char *input;
	char **result;
	while (1)
	{
		input = readline("Minishell: ");
		result = ft_split(input, ' ');
		printf("Command: %s\n", result[0]);
		printf("Additional: %s\n", result[1]);
		printf("Second Additional: %s\n", result[2]);
	}
	return (0);
}
