//
// Created by Shasta Glossu on 11/19/21.
//

#include "libft.h"

t_list *ft_lstfind(t_list *lst, char *key)
{
	while (lst)
	{
		if (!ft_strncmp(lst->val, key, ft_strlen(key)) && \
		(ft_strlen(key) == ft_strlen(lst->val) || lst->val[ft_strlen(key)] == '='))
			return (lst);
		lst = lst->next;
	}
	return NULL;
}
