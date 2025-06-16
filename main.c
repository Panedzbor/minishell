#include "minishell.h"

int	main(void)
{
	char *r;
	while (1)
	{
		r = readline("Minishell: ");
		//TODO: delete printf. 
		printf("%s\n", r);
	}
	return (0);
}
