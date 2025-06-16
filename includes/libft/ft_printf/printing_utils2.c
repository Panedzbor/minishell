/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:12:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:48:07 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_space(t_form mod, signed int num)
{
	if (mod.end == 'd' || mod.end == 'i' || (mod.end == 'p' && num > 0))
	{
		if (mod.flags[1] == ' ' && num >= 0)
		{
			write(1, " ", 1);
			return (1);
		}
	}
	return (0);
}

void	capitalize_hex(char c)
{
	char	buf[2];

	buf[0] = ft_toupper(c);
	buf[1] = '\0';
	write(1, buf, 1);
}
