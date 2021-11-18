#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del && lst)
	{
		del(lst->val);
		free(lst);
	}
}
