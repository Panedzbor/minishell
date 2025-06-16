/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:07:38 by earutiun          #+#    #+#             */
/*   Updated: 2024/11/18 18:55:20 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elements, size_t size)
{
	void	*memory;

	if (size != 0)
	{
		if (elements > (SIZE_MAX / size))
			return (NULL);
	}
	memory = malloc(elements * size);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, elements * size);
	return (memory);
}
