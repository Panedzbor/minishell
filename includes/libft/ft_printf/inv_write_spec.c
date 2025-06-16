/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inv_write_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:30 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/25 17:46:08 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_dig(char *str, int i, bool *digflg);
static int	proc_dot(char *str, int i, bool *digflg);
static void	define_x(bool *digflg, char *str, int i, int *x);
static int	write_astn(char *num_u, t_arrs *arrs, int x);

int	write_spcf(size_t offset, t_form *mod, t_arrs *arrs, char *str)
{
	bool	digflg;
	size_t	i;
	int		x;
	int		n;
	char	*num_u;

	num_u = NULL;
	digflg = false;
	init_ints(&i, &n, &x);
	while (i < offset && mod->end != '\0')
	{
		n += write_dig(str, i, &digflg);
		if (str[i] == '.' && i < offset && arrs->astn[1] >= 0)
			n += proc_dot(str, (int)i, &digflg);
		if (str[i] == '*')
		{
			define_x(&digflg, str, i, &x);
			num_u = convert_unum(arrs, x, str, offset);
			if (!num_u || num_u == str)
				return (inv_funct1(num_u, &n, mod));
			n += write_astn(num_u, arrs, x);
		}
		i++;
	}
	return (n);
}

static int	proc_dot(char *str, int i, bool *digflg)
{
	int	n;

	write(1, ".", 1);
	n = 1;
	if (!ft_isdigit(str[i + 1]) && str[i + 1] != '*')
	{
		write(1, "0", 1);
		n++;
	}
	*digflg = true;
	return (n);
}

static void	define_x(bool *digflg, char *str, int i, int *x)
{
	*digflg = true;
	if (str[i - 1] == '.')
		*x = 1;
	else
		*x = 0;
}

static int	write_astn(char *num_u, t_arrs *arrs, int x)
{
	int	y;
	int	n;

	y = 0;
	n = 0;
	while (num_u[y] != '\0')
	{
		if (x == 0 && (arrs->astn[0] == 0 || arrs->astn[0] == -2147483648))
		{
			if (arrs->astn[0] == -2147483648)
			{
				write(1, "18446744071562067968", 20);
				n = 20;
			}
			break ;
		}
		write(1, &num_u[y], 1);
		n++;
		y++;
	}
	free (num_u);
	return (n);
}

static int	write_dig(char *str, int i, bool *digflg)
{
	int	n;

	n = 0;
	if (!isflag_pf(str[i]) && str[i] != '%' && str[i] != '.' && str[i] != '*')
	{
		write(1, &str[i], 1);
		*digflg = true;
		n++;
	}
	if (*digflg && str[i] == '0')
	{
		write(1, "0", 1);
		n++;
	}
	return (n);
}
