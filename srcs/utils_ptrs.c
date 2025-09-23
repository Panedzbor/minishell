#include "../includes/minishell.h"

void free_and_reset_ptrs(int amount, void **ptr, ...)
{
	va_list	args;
	int i;

	va_start(args, ptr);
	i = 0;
	while (i < amount)
	{
		if (i > 0)
			ptr = va_arg(args, void **);
		if (*ptr)
		{
			free(*ptr);
			*ptr = NULL;
		}
		i++;
	}
	va_end(args);
}

void check_ptr(void *ptr)
{
	if (!ptr)
		return ; //run error handler
}