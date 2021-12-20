/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:26:10 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:26:17 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **lst, t_list *elem)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	if (tmp == elem)
	{
		*lst = (*lst)->next;
		ft_lstdelone(tmp, free);
		return ;
	}
	while (tmp && tmp->next)
	{
		if (tmp->next == elem)
		{
			tmp2 = tmp->next->next;
			ft_lstdelone(tmp->next, free);
			tmp->next = tmp2;
			return ;
		}
		tmp = tmp->next;
	}
}
