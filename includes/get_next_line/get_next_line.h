/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:22:47 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/18 14:23:51 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_statvals
{
	char	*left;
	int		check;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	blen;
	int		fd;
}	t_st;

char	*get_next_line(int fd);
void	gnl_init_struct(t_st *st, int fd);
ssize_t	count_size(char *str);
char	*erase_left(t_st *st);
char *seach_env_var(char *var_name);

#endif
