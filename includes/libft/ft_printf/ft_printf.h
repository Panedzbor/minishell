/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:22:47 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:47:15 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdint.h>

typedef struct s_formatting
{
	char	flags[5];
	int		width;
	int		precis;
	int		trunc;
	int		len;
	char	end;
	bool	except;
}	t_form;

typedef struct s_arrays
{
	int		ext[2][2];
	int		astn[2];
	bool	astnumb[2];
	long	lnum[2];
}	t_arrs;

int		ft_printf(const char *fstring, ...);
size_t	find_ending(char *start, bool *val, bool *flend);
int		format_value(char *str, size_t offset, bool *valid, va_list args);
int		format_number(char *str, size_t offset, char fs, va_list args);
int		format_text(char *str, size_t offset, char end, va_list args);
void	extract_format_val(char *str, size_t offset, va_list args, t_form *mod);
int		allign_left(t_form mod, signed int snum, char *numstr);
int		allign_right(t_form mod, signed int snum, char *numstr);
int		field_fill_num(t_form mod, signed int snum, char fill);
int		write_sign(t_form mod, signed int num);
int		write_prefix(t_form mod, signed int snum);
int		write_arg(char *numstr, char end, int len);
int		precis_fill(t_form mod, int num);
int		write_space(t_form mod, signed int num);
int		get_sum(t_form mod, signed int snum);
void	capitalize_hex(char c);
char	*ft_utoa(unsigned int n);
char	*ft_xtoa(unsigned int n);
char	*ft_ptoa(uintptr_t n);
int		isflagnum_pf(char c);
int		isflag_pf(char c);
int		isnum_pf(char c);
bool	check_overflow(char *numstr);
bool	check_ending(char e);
void	init_struct(t_form *mod);
void	init_buf(char buf[3], char end);
void	init_arr(int *arr, int dim);
void	init_strarr(t_arrs *arrs);
void	init_ints(size_t *i, int *n, int *x);
int		write_str(t_arrs *arrs, char *str, size_t offset, t_form *mod);
int		write_spcf(size_t offset, t_form *mod, t_arrs *arrs, char *str);
void	def_dig(char *str, size_t i, size_t offset, bool *dig);
void	def_extpts(bool *dig, int (*ext)[2], int i);
int		check_exend(char e, char *str, int i, bool ex);
char	*convert_unum(t_arrs *arrs, int x, char *str, size_t offset);
int		inv_funct1(char *num_u, int *n, t_form *mod);
void	free_check(int arg, void *ptr);

#endif
