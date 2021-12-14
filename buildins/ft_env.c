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

int	ft_env(t_list *lst)
{
	if (!lst)
		return (1);
	while (lst)
	{
		ft_putendl_fd(lst->val, STDOUT_FILENO);
		lst = lst->next;
	}
	return (0); // не ошибка
}

