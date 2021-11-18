#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	if (!lst)
		return (0);
	count = 0;
	temp = lst;
	while (temp->next != NULL)
	{
		count++;
		temp = temp->next;
	}
	count++;
	return (count);
}
