/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:27:34 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:45:14 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	inv_funct1(char *num_u, int *n, t_form *mod)
{
	if (!num_u)
	{
		mod->except = false;
		return (-1);
	}
	mod->except = true;
	return (*n + 1);
}

void	free_check(int arg, void *ptr)
{
	if (arg > 0)
		free(ptr);
}
