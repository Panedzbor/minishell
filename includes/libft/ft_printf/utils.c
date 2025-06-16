/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:27:34 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:45:14 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_struct(t_form *mod)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mod->flags[i] = '_';
		i++;
	}
	mod->flags[4] = '\0';
	mod->precis = 0;
	mod->trunc = -1;
	mod->width = 0;
	mod->len = 0;
	mod->end = '0';
	mod->except = false;
}

void	init_buf(char buf[3], char end)
{
	buf[0] = '0';
	buf[1] = end;
	buf[2] = '\0';
}

void	init_arr(int *arr, int dim)
{
	int	i;

	i = 0;
	while (i < dim)
	{
		arr[i] = 0;
		i++;
	}
}

void	init_strarr(t_arrs *arrs)
{
	arrs->ext[0][0] = -1;
	arrs->ext[0][1] = -1;
	arrs->ext[1][0] = -1;
	arrs->ext[1][1] = -1;
	arrs->astnumb[0] = false;
	arrs->astnumb[1] = false;
	init_arr(arrs->astn, 2);
	arrs->lnum[0] = -1;
	arrs->lnum[1] = -1;
}

void	init_ints(size_t *i, int *n, int *x)
{
	*i = 0;
	*n = 0;
	*x = -1;
}
