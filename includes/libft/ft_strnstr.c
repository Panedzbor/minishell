/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:21:40 by earutiun          #+#    #+#             */
/*   Updated: 2024/11/26 14:07:32 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (to_find[0] == '\0')
		return ((char *)str);
	if (str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		k = i;
		while (to_find[j] == str[k] && k < len)
		{
			if (to_find[j + 1] == '\0' && k < len)
				return ((char *)&str[i]);
			j++;
			k++;
		}
		i++;
	}
	return (NULL);
}
