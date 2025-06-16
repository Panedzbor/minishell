/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:48:27 by earutiun          #+#    #+#             */
/*   Updated: 2024/12/14 18:11:29 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	define_start(char *str, const char *set, size_t set_size);
static size_t	define_end(char *str, const char *set, size_t set_size);

__attribute__((nonnull(1, 2)))
char	*ft_strtrim(const char *s1, const char *set)
{
	char	*new_str;
	size_t	set_size;
	size_t	start;
	size_t	end;
	size_t	len;

	set_size = ft_strlen(set);
	if (set_size == 0)
	{
		new_str = ft_strdup(s1);
		return (new_str);
	}
	start = define_start((char *)s1, set, set_size);
	if (start == ft_strlen(s1))
	{
		new_str = (char *)ft_calloc(1, sizeof(char));
		if (new_str == NULL)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	end = define_end((char *)s1, set, set_size);
	len = end - start + 1;
	new_str = ft_substr(s1, (unsigned int)start, len);
	return (new_str);
}

static size_t	define_start(char *str, const char *set, size_t set_size)
{
	size_t	i;
	size_t	y;

	i = 0;
	while (str[i] != '\0')
	{
		y = 0;
		while (set[y] != '\0')
		{
			if (set[y] == str[i])
				break ;
			y++;
		}
		if (y != set_size)
			i++;
		else
			break ;
	}
	return ((size_t)(&str[i] - str));
}

static size_t	define_end(char *str, const char *set, size_t set_size)
{
	size_t	i;
	size_t	y;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	while (&str[i] != str)
	{
		y = 0;
		while (set[y] != '\0')
		{
			if (set[y] == str[i])
				break ;
			y++;
		}
		if (y != set_size)
			i--;
		else
			break ;
	}
	return ((size_t)(&str[i] - str));
}
