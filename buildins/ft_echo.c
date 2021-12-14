/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:08:01 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:08:03 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_echo(t_list *arg)
{
	bool	line_break;

	line_break = true;
	arg = arg->next;
	if (arg && !ft_strcmp(arg->val, "-n"))
	{
		arg = arg->next;
		line_break = false;
	}
	while (arg)
	{
		if (!ft_strcmp((arg->val), "$?"))
			ft_putnbr_fd(s_status, STDOUT_FILENO);
		else
			ft_putstr_fd(arg->val, STDOUT_FILENO);
		if (arg->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		arg = arg->next;
	}
	if (line_break)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
