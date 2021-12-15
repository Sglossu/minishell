/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:10:18 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:10:28 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_list **env, t_list *exp, t_list *arg)
{
	t_list *tmp;

	arg = arg->next;
	while(arg)
	{
		tmp = ft_lstfind(*env, arg->val);
		if (tmp)
		{
			ft_lstremove(env, tmp);
			tmp = ft_lstfind(exp, arg->val);
			ft_lstremove(&exp, tmp);
		}
		arg = arg->next;
	}
}
