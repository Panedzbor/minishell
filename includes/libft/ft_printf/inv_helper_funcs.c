/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inv_helper_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:30 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:45:37 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	def_dig(char *str, size_t i, size_t offset, bool *dig)
{
	int	check;

	check = ft_isdigit(str[i]);
	if (check && str[i] != '0' && i < offset)
		*dig = true;
	if (!check)
		*dig = false;
}

void	def_extpts(bool *dig, int (*ext)[2], int i)
{
	if (*dig)
	{
		if (ext[0][0] == -1)
			ext[0][0] = i;
		else if (ext[0][1] > -1 && ext[1][0] == -1)
			ext[1][0] = i;
	}
	else
	{
		if (ext[0][0] > -1 && ext[1][0] == -1)
			ext[0][1] = i - 1;
		else if (ext[1][0] > -1 && ext[1][1] == -1)
			ext[1][1] = i - 1;
	}
}

int	check_exend(char e, char *str, int i, bool ex)
{
	if (e != '\0' && e != 'q' && e != 't' && e != 'h'
		&& e != 'j' && e != 'l' && e != 'z')
	{
		if (!ex)
		{
			write(1, &str[i], 1);
			return (1);
		}
		return (0);
	}
	return (-1);
}

char	*convert_unum(t_arrs *arrs, int x, char *str, size_t offset)
{
	char	*num_u;

	arrs->lnum[x] = arrs->astn[x];
	if (arrs->astn[0] < 0)
		arrs->lnum[0] = -(long)arrs->astn[0];
	if (arrs->astn[1] < 0 && x == 1)
	{
		write(1, &str[offset], 1);
		return (str);
	}
	num_u = ft_utoa((unsigned int)arrs->lnum[x]);
	return (num_u);
}
