/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:43:44 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:43:45 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_struct	mini_for_atoi(t_struct ptf, int nb, int minus)
{
	if (nb == -1 || nb == 0)
	{
		ptf.accuracy = nb;
		return (ptf);
	}
	ptf.accuracy = (int)nb * minus;
	return (ptf);
}

t_struct	ft_atoi_width(t_struct ptf, char *str)
{
	int			nb;

	nb = 0;
	if ((str[ptf.i] == 45) || (str[ptf.i] == 43))
	{
		if (str[ptf.i++] == 45)
			ptf.flag = '-';
	}
	while (str[ptf.i] >= '0' && str[ptf.i] <= '9')
	{
		nb = nb * 10 + (str[ptf.i] - '0');
		if (nb > 2147483645)
		{
			ptf.count = -1;
			return (ptf);
		}
		ptf.i++;
	}
	ptf.width = (int)nb;
	return (ptf);
}

t_struct	ft_atoi_accuracy(t_struct ptf, char *str)
{
	int			minus;
	int			nb;

	minus = 1;
	nb = 0;
	if ((str[ptf.i] == 45) || (str[ptf.i] == 43))
	{
		if (str[ptf.i++] == 45)
			minus = -1;
	}
	while (str[ptf.i] >= '0' && str[ptf.i] <= '9')
	{
		nb = nb * 10 + (str[ptf.i] - '0');
		if (nb * minus > 2147483645 || nb * minus < -2147483645)
		{
			ptf.count = -1;
			return (ptf);
		}
		ptf.i++;
	}
	return (mini_for_atoi(ptf, nb, minus));
}
