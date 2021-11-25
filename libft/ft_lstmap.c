#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_lst_tmp;

	if (!lst || !f)
		return (NULL);
	new_lst = ft_lstnew(f(lst->val));
	if (!new_lst)
		ft_lstclear(&lst, del);
	new_lst_tmp = new_lst;
	lst = lst->next;
	while (lst && new_lst)
	{
		new_lst->next = ft_lstnew(f(lst->val));
		if (!new_lst->next)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (new_lst_tmp);
}
