/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_digit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:42:53 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:42:54 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_struct	ft_for_else(t_struct ptf, int nb)
{
	if (ptf.minus == 1)
		ptf = ft_putchar(ptf, '-');
	while (ptf.accuracy > ft_strlen_nb(nb))
	{
		ptf = ft_putchar(ptf, '0');
		ptf.accuracy--;
	}
	ptf = ft_putnbr(ptf, nb);
	return (ptf);
}

static	t_struct	flag_minus(t_struct ptf, int nb)
{
	int	count;

	count = 0;
	ptf = ft_dig_min(ptf, nb);
	if (ptf.width >= ptf.accuracy)
	{
		if (ptf.minus == 1)
			ptf = ft_putchar(ptf, '-');
		while (ptf.accuracy > ft_strlen_nb(nb))
		{
			ptf = ft_putchar(ptf, '0');
			ptf.accuracy--;
			count++;
		}
		ptf = ft_putnbr(ptf, nb);
		while ((ptf.width > (ptf.accuracy + count + ptf.minus)) && ptf.width)
		{
			ptf = ft_putchar(ptf, ' ');
			ptf.width--;
		}
	}
	else
		ptf = ft_for_else(ptf, nb);
	return (ptf);
}

static	t_struct	flag_zero(t_struct ptf, int nb)
{
	if (ptf.width != 0)
		ptf.width -= ptf.minus;
	if (ptf.width >= ptf.accuracy)
		ptf = ft_dig_zero(ptf, nb);
	else
	{
		if (ptf.temp < 0)
			ptf.accuracy -= ptf.minus;
		ptf = ft_for_else(ptf, nb);
	}
	return (ptf);
}

static	t_struct	without_flag(t_struct ptf, int nb)
{
	if ((ptf.accuracy < ft_strlen_nb(nb)) && (ptf.accuracy || nb))
		ptf.accuracy = ft_strlen_nb(nb);
	if (ptf.width >= ptf.accuracy)
	{
		while (ptf.width > (ptf.accuracy + ptf.minus) && ptf.width)
		{
			ptf = ft_putchar(ptf, ' ');
			ptf.width--;
		}
		if (ptf.minus == 1)
			ptf = ft_putchar(ptf, '-');
		while (ptf.accuracy > ft_strlen_nb(nb))
		{
			ptf = ft_putchar(ptf, '0');
			ptf.accuracy--;
		}
		ptf = ft_putnbr(ptf, nb);
	}
	else
		ptf = ft_for_else(ptf, nb);
	return (ptf);
}

t_struct	for_digit(t_struct ptf)
{
	int	nb;

	nb = va_arg(ptf.ap, int);
	if (nb < 0)
	{
		nb = -nb;
		ptf.minus = 1;
	}
	if (ptf.flag == '-')
		ptf = flag_minus(ptf, nb);
	else if (ptf.flag == 0)
	{
		if ((ptf.accuracy < ft_strlen_inint(nb)) && (ptf.accuracy || nb) && \
		(ptf.accuracy != -2))
			ptf.accuracy = ft_strlen_inint(nb);
		ptf = flag_zero(ptf, nb);
	}
	else
		ptf = without_flag(ptf, nb);
	return (ptf);
}
