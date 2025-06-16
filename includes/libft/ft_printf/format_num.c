/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:33:03 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:43:53 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_d(char *str, size_t offset, va_list args);
static int	format_u(char *str, size_t offset, va_list args);
static int	format_x(char *str, size_t offset, va_list args);
static int	format_p(char *str, size_t offset, va_list args);

int	format_number(char *str, size_t offset, char end, va_list args)
{
	if (end == 'd' || end == 'i')
		return (format_d(str, offset, args));
	else if (end == 'u')
		return (format_u(str, offset, args));
	else if (end == 'x' || end == 'X')
		return (format_x(str, offset, args));
	else if (end == 'p')
		return (format_p(str, offset, args));
	return (0);
}

static int	format_d(char *str, size_t offset, va_list args)
{
	int			num;
	const char	*numstr;
	t_form		mod;

	init_struct(&mod);
	extract_format_val(str, offset, args, &mod);
	num = va_arg(args, int);
	numstr = (const char *)ft_itoa(num);
	mod.len = ft_strlen((char *)numstr);
	if (num < 0)
		mod.len -= 1;
	if (num == 0 && mod.precis == 0 && mod.flags[3] == '.')
	{
		free((void *)numstr);
		numstr = "";
		mod.len = 0;
	}
	if (mod.flags[2] == '-' || mod.width < 0)
		num = allign_left(mod, num, (char *)numstr);
	else
		num = allign_right(mod, num, (char *)numstr);
	free_check(mod.len, (void *)numstr);
	return (num);
}

static int	format_u(char *str, size_t offset, va_list args)
{
	unsigned int	num;
	const char		*numstr;
	t_form			mod;

	init_struct(&mod);
	extract_format_val(str, offset, args, &mod);
	num = va_arg(args, unsigned int);
	numstr = (const char *)ft_utoa(num);
	mod.len = ft_strlen((char *)numstr);
	if (num == 0 && mod.precis == 0 && mod.flags[3] == '.')
	{
		free((void *)numstr);
		numstr = "";
		mod.len = 0;
	}
	if (mod.flags[2] == '-' || mod.width < 0)
		num = allign_left(mod, 1, (char *)numstr);
	else
		num = allign_right(mod, 1, (char *)numstr);
	free_check(mod.len, (void *)numstr);
	return (num);
}

static int	format_x(char *str, size_t offset, va_list args)
{
	unsigned int	num;
	const char		*numstr;
	t_form			mod;
	int				i;

	i = 0;
	init_struct(&mod);
	extract_format_val(str, offset, args, &mod);
	num = va_arg(args, uintptr_t);
	if (num > 0)
		i = 1;
	numstr = (const char *)ft_xtoa((unsigned int)num);
	mod.len = ft_strlen((char *)numstr);
	if (num == 0 && mod.precis == 0 && mod.flags[3] == '.')
	{
		free((void *)numstr);
		numstr = "";
		mod.len = 0;
	}
	if (mod.flags[2] == '-' || mod.width < 0)
		i = allign_left(mod, i, (char *)numstr);
	else
		i = allign_right(mod, i, (char *)numstr);
	free_check(mod.len, (void *)numstr);
	return (i);
}

static int	format_p(char *str, size_t offset, va_list args)
{
	void		*ptr;
	const char	*numstr;
	t_form		mod;
	int			i;

	i = 0;
	init_struct(&mod);
	extract_format_val(str, offset, args, &mod);
	ptr = va_arg(args, void *);
	if (!ptr)
		numstr = "(nil)";
	if (ptr)
		numstr = (const char *)ft_ptoa((uintptr_t)ptr);
	if (ptr)
		i = 1;
	mod.len = ft_strlen((char *)numstr);
	if (mod.trunc == 0 && mod.flags[3] != '.')
		mod.trunc = mod.len;
	if (mod.flags[2] == '-' || mod.width < 0)
		i = allign_left(mod, i, (char *)numstr);
	else
		i = allign_right(mod, i, (char *)numstr);
	if (ptr)
		free((void *)numstr);
	return (i);
}
