/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:51:52 by earutiun          #+#    #+#             */
/*   Updated: 2024/11/20 18:54:10 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	forward_copying(unsigned char *d, const unsigned char *s, int na);
static void	backward_copying(unsigned char *d, const unsigned char *s, int na);

__attribute__((nonnull(1, 2)))
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	int					na;

	d = (unsigned char *) dest;
	s = (const unsigned char *)src;
	na = (int)n;
	if (d < s)
		forward_copying(d, s, na);
	else if (d > s)
		backward_copying(d, s, na);
	return (dest);
}

static void	forward_copying(unsigned char *d, const unsigned char *s, int na)
{
	int	i;

	i = 0;
	while (i < na)
	{
		d[i] = s[i];
		i++;
	}
}

static void	backward_copying(unsigned char *d, const unsigned char *s, int na)
{
	int	i;

	i = 0;
	while (i < na)
		i++;
	i--;
	while (i >= 0)
	{
		d[i] = s[i];
		i--;
	}
}
