#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (temp == NULL)
	{
//		new->next = NULL;
		*lst = new;
		return ;
	}
	while (temp->next)
	{
		temp = temp->next;
		write(1, "hui\n", 4);
	}
	temp->next = new;
}
