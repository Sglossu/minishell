#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		if (lst->val)
			f(lst->val);
		lst = lst->next;
	}
}
