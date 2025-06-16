/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:12:04 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:48:54 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	valid_zero(char *str, size_t offset, bool *val, size_t *i);
static void	valid_digit(char *str, size_t offset, bool *val, size_t *i);
static void	valid_asterisk(char *str, size_t offset, bool *val, size_t *i);

void	valid_numerics(char *str, size_t offset, bool *val)
{
	size_t	i;

	i = 1;
	while (i < offset && *val == true)
	{
		if (str[i] == '0')
			valid_zero(str, offset, val, &i);
		else if (ft_isdigit(str[i]) == 1)
			valid_digit(str, offset, val, &i);
		else if (str[i] == '*')
			valid_asterisk(str, offset, val, &i);
		i++;
	}
}

static void	valid_zero(char *str, size_t offset, bool *val, size_t *i)
{
	if (ft_isdigit(str[*i - 1]) == 1 || str[*i - 1] == '.')
	{
		if (ft_isdigit(str[*i + 1]) == 0
			&& str[*i + 1] != '.' && str[*i + 1] != str[offset])
			*val = false;
	}
}

static void	valid_digit(char *str, size_t offset, bool *val, size_t *i)
{
	if (ft_isdigit(str[*i + 1]) == 0
		&& str[*i + 1] != '.' && str[*i + 1] != str[offset])
		*val = false;
}

static void	valid_asterisk(char *str, size_t offset, bool *val, size_t *i)
{
	if (str[*i + 1] != '.' && str[*i + 1] != str[offset])
		*val = false;
}
