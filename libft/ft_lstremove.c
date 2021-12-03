//
// Created by Shasta Glossu on 11/19/21.
//
#include "libft.h"

void	ft_lstremove(t_list **lst, t_list *elem)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	if (!elem)
		return ;
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
