/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:47 by earutiun          #+#    #+#             */
/*   Updated: 2024/12/10 13:11:55 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include "./ft_printf/ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_variable_storage
{
	size_t		words;
	char		**array;
	size_t		*iarr;
	char		set[2];
	bool		no_words;
}	t_vs;

int		ft_atoi(const char *str)
		__attribute__((nonnull));
void	ft_bzero(void *s, size_t n)
		__attribute__((nonnull(1)));
void	*ft_calloc(size_t elements, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n)__attribute__((nonnull(1)));
int		ft_memcmp(const void *s1, const void *s2, size_t n)
		__attribute__((nonnull(1, 2)));
void	*ft_memcpy(void *dest, const void *src, size_t n)
		__attribute__((nonnull(1, 2)));
void	*ft_memmove(void *dest, const void *src, size_t n)
		__attribute__((nonnull(1, 2)));
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c)__attribute__((nonnull(1)));
char	*ft_strdup(const char *s)__attribute__((nonnull));
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str)__attribute__((nonnull));
int		ft_strncmp(const char *s1, const char *s2, size_t n)
		__attribute__((nonnull(1, 2)));
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strrchr(const char *s, int c)__attribute__((nonnull(1)));
int		ft_tolower(int ch);
int		ft_toupper(int ch);
char	*ft_substr(char const *s, unsigned int start, size_t len)
		__attribute__((nonnull));
char	*ft_strjoin(char const *s1, char const *s2)
		__attribute__((nonnull(1, 2)));
char	*ft_strtrim(char const *s1, char const *set)
		__attribute__((nonnull(1, 2)));
char	**ft_split(const char *s, char c)__attribute__((nonnull(1)));
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
		__attribute__((nonnull));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
