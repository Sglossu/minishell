/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_functions_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:42:39 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:42:41 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_struct	ft_point_2(t_struct ptf, unsigned long nb)
{
	if (ptf.temp < 0)
	{
		ptf.width = ft_diglenlong(nb) + 2;
		ptf.accuracy = 1;
	}
	if (ptf.flag != 0)
	{
		if (ptf.accuracy < ft_diglenlong(nb) && ptf.accuracy != 0)
			ptf.accuracy = ft_diglenlong(nb);
	}
	return (ptf);
}
