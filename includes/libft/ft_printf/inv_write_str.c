/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inv_write_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:30 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:46:35 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*check_extval(int (*ext)[2], char *str, int i);
static void	get_astn(size_t offset, t_arrs *arrs, t_form mod, char *str);
static bool	check_excpt(char e, char n);
static int	write_flg(t_form mod, int *astn);

int	write_str(t_arrs *arrs, char *str, size_t offset, t_form *mod)
{
	int	n;
	int	n2;

	n = 0;
	if (!check_extval(arrs->ext, str, 0) || !check_extval(arrs->ext, str, 1))
		return (0);
	get_astn(offset, arrs, *mod, str);
	if (check_excpt(mod->end, str[offset + 1]))
		return (0);
	if (mod->end != '\0')
		n += write_flg(*mod, arrs->astn);
	n2 = write_spcf(offset, mod, arrs, str);
	if (n2 < 0)
		return (-1);
	n += n2;
	return (n);
}

static char	*check_extval(int (*ext)[2], char *str, int i)
{
	int		num;
	char	*numstr;

	num = 1;
	if (ext[i][0] > -1 && ext[i][1] > -1)
	{
		numstr = ft_substr(
				(const char *)str, ext[i][0], ext[i][1] - ext[i][0] + 1);
		if (!numstr)
			return (NULL);
		if (check_overflow(numstr))
			num = -1;
		free(numstr);
		if (num == -1)
			return (NULL);
	}
	return (str);
}

static void	get_astn(size_t offset, t_arrs *arrs, t_form mod, char *str)
{
	size_t	i;

	i = 0;
	while (i < offset)
	{
		if (str[i] == '*' && !arrs->astnumb[0])
		{
			arrs->astn[0] = mod.width;
			arrs->astnumb[0] = true;
		}
		if (str[i] == '*' && arrs->astnumb[0] && !arrs->astnumb[1])
		{
			arrs->astn[1] = mod.precis;
			arrs->astnumb[1] = true;
		}
		i++;
	}
}

static bool	check_excpt(char e, char n)
{
	if ((e == 'q' || e == 't' || e == 'h'
			|| e == 'j' || e == 'l' || e == 'z') && n == '\0')
		return (true);
	return (false);
}

static int	write_flg(t_form mod, int *astn)
{
	int	i;
	int	n;

	write(1, "%", 1);
	n = 1;
	i = 0;
	while (i < 3)
	{
		if (i == 2 && mod.flags[i] != '-' && astn[0] < 0)
		{
			write(1, "-", 1);
			n++;
		}
		if (mod.flags[i] != '_')
		{
			write(1, &mod.flags[i], 1);
			n++;
		}
		i++;
	}
	return (n);
}
