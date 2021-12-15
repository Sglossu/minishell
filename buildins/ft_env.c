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

void	ft_env(t_list *lst)
{
	while (lst)
	{
		ft_putendl_fd(lst->val, STDOUT_FILENO);
		lst = lst->next;
	}
	s_status = 0;
}

