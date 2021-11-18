//
// Created by Shasta Glossu on 11/19/21.
//

#include "../includes/minishell.h"

int ft_unset(t_list **env, t_list *arg)
{
	t_list *tmp;

	arg = arg->next;
	while(arg)
	{
		tmp = ft_lstfind(*env, arg->val);
		if (tmp)
		{
			ft_lstremove(env, tmp);
		}
		arg = arg->next;
	}
	return (0);
}