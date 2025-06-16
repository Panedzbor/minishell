/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:12:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:47:40 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_arg(char *numstr, char end, int len)
{
	int	i;
	int	printed;

	i = 0;
	printed = 0;
	while (numstr[i] != '\0')
	{
		if (end == 's' && i == len)
			break ;
		if (numstr[i] != '-' || (end != 'd' && end != 'i'))
		{
			if (end != 'X')
				write(1, &numstr[i], 1);
			else
				capitalize_hex(numstr[i]);
			printed++;
		}
		i++;
	}
	if (end == 'c' && numstr[0] == 0)
	{
		write(1, "\0", 1);
		printed++;
	}
	return (printed);
}

int	precis_fill(t_form mod, int num)
{
	int	i;

	if (mod.end == 'p' && num == 0)
		return (0);
	i = 0;
	while (i < mod.precis - mod.len)
	{
		write(1, "0", 1);
		i++;
	}
	return (i);
}

int	write_prefix(t_form mod, signed int num)
{
	if (num == 0)
		return (0);
	if (mod.end == 'p')
	{
		write(1, "0x", 2);
		return (2);
	}
	else if (mod.end == 'x' && mod.flags[0] == '#')
	{
		write(1, "0x", 2);
		return (2);
	}
	else if (mod.end == 'X' && mod.flags[0] == '#')
	{
		write(1, "0X", 2);
		return (2);
	}
	return (0);
}

int	write_sign(t_form mod, signed int num)
{
	if (num < 0)
	{
		write(1, "-", 1);
		return (1);
	}
	else if (mod.flags[1] == '+' && (mod.end == 'd' || mod.end == 'i'
			|| (mod.end == 'p' && num > 0)))
	{
		write(1, "+", 1);
		return (1);
	}
	return (0);
}

int	field_fill_num(t_form mod, signed int snum, char fill)
{
	int		i;
	int		sum;
	char	buf[2];

	i = 0;
	sum = get_sum(mod, snum);
	if (mod.end == 'c' || mod.end == 's' || (mod.end == 'p' && snum == 0))
		fill = ' ';
	buf[0] = fill;
	buf[1] = '\0';
	if (mod.width < 0)
		mod.width *= (-1);
	if (mod.width > sum)
	{
		while (i < mod.width - sum)
		{
			write(1, buf, 1);
			i++;
		}
	}
	return (i);
}
