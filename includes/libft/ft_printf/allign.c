/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:15:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:53:30 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	allign_left(t_form mod, signed int snum, char *numstr)
{
	int	sum;

	if (mod.except)
		return (-1);
	sum = write_sign(mod, snum);
	sum += write_space(mod, snum);
	sum += write_prefix(mod, snum);
	sum += precis_fill(mod, snum);
	sum += write_arg(numstr, mod.end, mod.len);
	sum += field_fill_num(mod, snum, ' ');
	return (sum);
}

int	allign_right(t_form mod, signed int snum, char *numstr)
{
	int	sum;

	if (mod.except)
		return (-1);
	if (mod.flags[2] != '0' || mod.flags[3] == '.')
	{
		sum = write_space(mod, snum);
		sum += field_fill_num(mod, snum, ' ');
		sum += write_sign(mod, snum);
		sum += write_prefix(mod, snum);
		sum += precis_fill(mod, snum);
		sum += write_arg(numstr, mod.end, mod.len);
	}
	else
	{
		sum = write_sign(mod, snum);
		sum += write_space(mod, snum);
		sum += write_prefix(mod, snum);
		sum += field_fill_num(mod, snum, '0');
		sum += write_arg(numstr, mod.end, mod.len);
	}
	return (sum);
}
