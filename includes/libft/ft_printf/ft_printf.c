/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:14:25 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:44:41 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	check_specifier(char *start, bool *valid);
static size_t	process_specifier(
					bool *valid, const char *fstring,
					va_list args, int *counter);

int	ft_printf(const char *fstring, ...)
{
	va_list	args;
	size_t	pos;
	int		counter;
	bool	valid[2];

	va_start(args, fstring);
	valid[0] = true;
	valid[1] = false;
	pos = 0;
	counter = 0;
	while (fstring[pos] != '\0')
	{
		if (fstring[pos] == '%')
		{
			pos += process_specifier(valid, &fstring[pos], args, &counter);
			continue ;
		}
		write(1, &fstring[pos], 1);
		counter++;
		pos++;
	}
	va_end(args);
	return (counter);
}

static size_t	process_specifier(
	bool *valid, const char *fstring, va_list args, int *counter)
{
	size_t	fend;
	int		count_check;

	valid[0] = true;
	fend = check_specifier((char *)fstring, valid);
	count_check = format_value((char *)fstring, fend, valid, args);
	if (count_check >= 0)
		*counter += count_check;
	else
		*counter = count_check;
	return (fend + 1);
}

static size_t	check_specifier(char *start, bool *valid)
{
	size_t	offset;
	bool	val;

	val = true;
	offset = find_ending(start, &val, &valid[1]);
	if (start[offset] == '\0')
		offset -= 1;
	if (val == true && valid[0] == true)
		return (offset);
	if (val == true && valid[0] == false)
		return (0);
	valid[0] = false;
	return (offset);
}
