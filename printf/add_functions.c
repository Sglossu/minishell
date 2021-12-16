/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:42:23 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:42:24 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_struct	about_u(t_struct ptf, unsigned int nb)
{
	while (ptf.width - ptf.accuracy > 0)
	{
		ptf = ft_putchar(ptf, ' ');
		ptf.width--;
	}
	while (ptf.width > ft_strlen_nb(nb))
	{
		ptf = ft_putchar(ptf, '0');
		ptf.width--;
	}
	ptf = ft_putnbr(ptf, nb);
	return (ptf);
}

t_struct	about_x(t_struct ptf, int nb, int type)
{
	while (ptf.width - ptf.accuracy > 0)
	{
		ptf = ft_putchar(ptf, ' ');
		ptf.width--;
	}
	while (ptf.width > ft_diglen16(nb))
	{
		ptf = ft_putchar(ptf, '0');
		ptf.width--;
	}
	ptf = ft_putnbr16(ptf, nb, type);
	return (ptf);
}

t_struct	about_p(t_struct ptf, unsigned long nb)
{
	while (ptf.width - ptf.accuracy > 2)
	{
		ptf = ft_putchar(ptf, ' ');
		ptf.width--;
	}
	while (ptf.width - 2 > ft_diglenlong(nb))
	{
		ptf = ft_putchar(ptf, '0');
		ptf.width--;
	}
	ptf = ft_putchar(ptf, '0');
	ptf = ft_putchar(ptf, 'x');
	ptf = ft_putnbrlong(ptf, nb);
	return (ptf);
}

t_struct	ft_space(t_struct ptf, char *str)
{
	while (str[ptf.i] == ' ' || str[ptf.i] == '0' || str[ptf.i] == '-')
	{
		ptf.i++;
		ptf.space++;
	}
	return (ptf);
}

int	if_s(t_struct ptf, char *str)
{
	int	i;

	i = ptf.i;
	while (str[i] == ' ')
		i++;
	if (str[i] == 's')
		return (1);
	return (0);
}
