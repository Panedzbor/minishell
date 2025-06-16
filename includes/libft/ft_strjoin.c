/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:38:25 by earutiun          #+#    #+#             */
/*   Updated: 2024/11/21 19:49:27 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n);

__attribute__((nonnull(1, 2)))
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	size_t	len;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	len = s1len + s2len;
	newstr = (char *)ft_calloc(len + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	if (len > 0)
	{
		ft_strncpy(newstr, s1, s1len);
		ft_strncpy(&newstr[s1len], s2, s2len);
	}
	else
		newstr[0] = '\0';
	return (newstr);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
