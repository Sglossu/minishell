/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:44:01 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:44:02 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_struct	first_init_struct(t_struct ptf)
{
	ptf.flag = '1';
	ptf.width = 0;
	ptf.accuracy = -2;
	ptf.i = 0;
	ptf.count = 0;
	ptf.minus = 0;
	ptf.space = 0;
	ptf.temp = 0;
	ptf.temp_w = 0;
	return (ptf);
}

t_struct	second_init_struct(t_struct ptf)
{
	ptf.flag = '1';
	ptf.width = 0;
	ptf.accuracy = -2;
	ptf.minus = 0;
	ptf.space = 0;
	ptf.temp = 0;
	ptf.temp_w = 0;
	return (ptf);
}
