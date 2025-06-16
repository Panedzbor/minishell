/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:45:52 by earutiun          #+#    #+#             */
/*   Updated: 2024/12/06 21:56:06 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	convert(char *number, unsigned int nb);
static void	assign_zero(char *number);
static void	write_minus(int n, int fd);
static void	print_out(char *number, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	char				number[11];
	unsigned int		nb;

	if (n < 0)
		nb = (-1) * n;
	else
		nb = n;
	assign_zero(number);
	convert(number, nb);
	write_minus(n, fd);
	print_out(number, fd);
}

static void	print_out(char *number, int fd)
{
	int	l;

	l = 0;
	while (l < 10)
	{
		if (number[l] != '\0')
		{
			write(fd, &number[l], 1);
		}
		l++;
	}
}

static void	write_minus(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
}

static void	convert(char *number, unsigned int nb)
{
	int	r;
	int	i;
	int	c;

	c = 9;
	r = nb % 10;
	i = nb / 10;
	number[c] = r + '0';
	c--;
	while (i > 0)
	{
		nb = i;
		r = nb % 10;
		i = nb / 10;
		number[c] = r + '0';
		c--;
	}
}

static void	assign_zero(char *number)
{
	int	l;

	l = 0;
	while (l < 11)
	{
		number[l] = '\0';
		l++;
	}
}
