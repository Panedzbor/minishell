/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:12:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:48:29 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	define_prefix(t_form mod, int snum);
static int	define_sign(t_form mod, int snum);
static int	sum_val(int *values, t_form mod, int snum);

int	get_sum(t_form mod, signed int snum)
{
	int	sppl[4];
	int	sum;

	init_arr(sppl, 4);
	sppl[0] = define_sign(mod, snum);
	sppl[1] = define_prefix(mod, snum);
	sppl[2] = mod.precis;
	sppl[3] = mod.len;
	sum = sum_val(sppl, mod, snum);
	return (sum);
}

static int	sum_val(int *values, t_form mod, int snum)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < 4)
	{
		if (i == 2)
		{
			if (values[2] > values[3] && !(mod.end == 'p' && snum == 0))
				values[i] = values[2] - values[3];
			else
				values[i] = 0;
		}
		result += values[i];
		i++;
	}
	return (result);
}

static int	define_sign(t_form mod, int snum)
{
	if (snum < 0)
		return (1);
	if (mod.flags[1] != '_'
		&& (mod.end == 'd' || mod.end == 'i' || (mod.end == 'p' && snum > 0)))
		return (1);
	return (0);
}

static int	define_prefix(t_form mod, int snum)
{
	if (snum == 0)
		return (0);
	if (mod.end == 'p')
		return (2);
	if ((mod.end == 'x' || mod.end == 'X') && mod.flags[0] == '#')
		return (2);
	return (0);
}
