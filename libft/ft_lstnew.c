#include "libft.h"

t_list	*ft_lstnew(void *val)
{
	t_list	*new_elem;

	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->val = val;
	new_elem->next = NULL;
	return (new_elem);
}
