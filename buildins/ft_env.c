//
// Created by Shasta Glossu on 11/18/21.
//

//t_list	*lst = 0;
//ft_lstadd_back(&lst, ft_lstnew(ft_strdup("12345678")));
//ft_lstadd_back(&lst, ft_lstnew(ft_strdup("styshfj")));
//ft_lstadd_back(&lst, ft_lstnew(ft_strdup("sh   yh sst")));
//ft_lstadd_back(&lst, ft_lstnew(ft_strdup("uytrr89  cvbmn")));

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

