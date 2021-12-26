/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:08:30 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:08:36 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_list *arg, t_list *lst)
{
	if (arg->next)
	{
		g_status = 127;
		ft_printf(2, "env: %s: No such file or directory\n", arg->next->val);
		return ;
	}
	while (lst)
	{
		if (ft_strchr(lst->val, '='))
			ft_putendl_fd(lst->val, STDOUT_FILENO);
		lst = lst->next;
	}
	g_status = 0;
}
