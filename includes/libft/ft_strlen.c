/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:21:35 by earutiun          #+#    #+#             */
/*   Updated: 2024/11/25 17:09:00 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

__attribute__((nonnull))
size_t	ft_strlen(const char *str)
{
	size_t	chars;

	chars = 0;
	while (str[chars] != '\0')
		chars++;
	return (chars);
}
