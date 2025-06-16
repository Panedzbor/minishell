/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:45:52 by earutiun          #+#    #+#             */
/*   Updated: 2024/12/06 19:55:31 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_digits(unsigned int nb);
static void		convert(char *number, unsigned int nb, int digits);

char	*ft_itoa(int n)
{
	unsigned int		nb;
	int					digits;
	char				*ptr;

	digits = 0;
	if (n < 0)
	{
		nb = (-1) * n;
		digits++;
	}
	else
		nb = n;
	digits += count_digits(nb);
	ptr = (char *)ft_calloc(digits + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (n < 0)
		ptr[0] = '-';
	convert(ptr, nb, digits);
	ptr[digits] = '\0';
	return (ptr);
}

static int	count_digits(unsigned int nb)
{
	int	counter;

	counter = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		counter++;
	}
	return (counter);
}

static void	convert(char *number, unsigned int nb, int digits)
{
	int	r;
	int	i;

	r = nb % 10;
	i = nb / 10;
	number[digits - 1] = r + '0';
	digits--;
	while (i > 0)
	{
		nb = i;
		r = nb % 10;
		i = nb / 10;
		number[digits - 1] = r + '0';
		digits--;
	}
}
