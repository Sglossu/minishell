/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:42:47 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:42:48 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_struct	without_flag(t_struct ptf, char c)
{
	while (ptf.width > 1)
	{
		ptf = ft_putchar(ptf, ' ');
		ptf.width--;
	}
	ptf = ft_putchar(ptf, c);
	return (ptf);
}

static	t_struct	flag_zero(t_struct ptf, char c)
{
	while (ptf.width > 1)
	{
		ptf = ft_putchar(ptf, '0');
		ptf.width--;
	}
	ptf = ft_putchar(ptf, c);
	return (ptf);
}

static	t_struct	flag_minus(t_struct ptf, char c)
{
	ptf = ft_putchar(ptf, c);
	while (ptf.width > 1)
	{
		ptf = ft_putchar(ptf, ' ');
		ptf.width--;
	}
	return (ptf);
}

t_struct	for_char(t_struct ptf, char c)
{
	if (c != '%')
		c = va_arg(ptf.ap, int);
	if (ptf.flag == '-')
		ptf = flag_minus(ptf, c);
	else if (ptf.flag == 0)
		ptf = flag_zero(ptf, c);
	else
		ptf = without_flag(ptf, c);
	return (ptf);
}
