/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:18:26 by earutiun          #+#    #+#             */
/*   Updated: 2024/11/20 18:47:32 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

__attribute__((nonnull(1)))
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*sa;

	sa = s;
	i = 0;
	while (i < n)
	{
		if (sa[i] == (unsigned char)c)
			return ((void *)&sa[i]);
		i++;
	}
	return (NULL);
}
