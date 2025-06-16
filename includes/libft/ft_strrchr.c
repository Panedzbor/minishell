/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:09 by earutiun          #+#    #+#             */
/*   Updated: 2024/12/14 18:10:09 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

__attribute__((nonnull(1)))
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		found;
	char	*temp;

	i = 0;
	found = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			temp = (char *)&s[i];
			found = 1;
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	if (found == 1)
		return (temp);
	return (NULL);
}
