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

int	check_flag_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
		i++;
	else
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(t_list *arg)
{
	bool	line_break;

	line_break = true;
	arg = arg->next;
	while (arg && !check_flag_n(arg->val))
	{
		arg = arg->next;
		line_break = false;
	}
	while (arg)
	{
		ft_putstr_fd(arg->val, STDOUT_FILENO);
		if (arg->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		arg = arg->next;
	}
	if (line_break)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_status = 0;
	return (g_status);
}
