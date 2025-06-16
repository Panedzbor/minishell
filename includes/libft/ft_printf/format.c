/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:28:30 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:43:17 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	valid_format(char *str, size_t offset, va_list args);
static int	invalid_format(char *str, size_t offset, va_list args, bool flend);

int	format_value(char *str, size_t offset, bool *valid, va_list args)
{
	if (valid[0] == true)
		return (valid_format(str, offset, args));
	else
		return (invalid_format(str, offset, args, valid[1]));
}

static int	valid_format(char *str, size_t offset, va_list args)
{
	char	end;

	end = str[offset];
	if (end == 'c' || end == 's' || end == '%')
		return (format_text(str, offset, end, args));
	else
		return (format_number(str, offset, end, args));
}

static int	invalid_format(char *str, size_t offset, va_list args, bool flend)
{
	int		i;
	int		n;
	t_form	mod;
	t_arrs	arrs;
	bool	dig;

	if (offset == 0)
		return (-1);
	init_struct(&mod);
	mod.len = (int)offset;
	if ((isflagnum_pf(str[offset])) && !flend && !str[offset + 1])
		mod.len += 1;
	extract_format_val(str, mod.len, args, &mod);
	init_strarr(&arrs);
	dig = false;
	i = 0;
	while ((size_t)i <= offset)
	{
		def_dig(str, (size_t)i, offset, &dig);
		def_extpts(&dig, arrs.ext, i++);
	}
	n = write_str(&arrs, str, offset, &mod);
	if (n < 0)
		return (0);
	return (n + check_exend(mod.end, str, i - 1, mod.except));
}
