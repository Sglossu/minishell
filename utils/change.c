#include "../includes/minishell.h"

void	change_after_equals_in_list(t_all *all, t_list *tmp, char *str)
{
	ft_lstremove(&all->env, tmp);
	ft_lstadd_back(&all->env, ft_lstnew(str));
}