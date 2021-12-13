//
// Created by Shasta Glossu on 11/20/21.
//

#include "../includes/minishell.h"

t_list	*init_lst_env_or_exp(char **buf)
{
	t_list	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (buf[i])
	{
		ft_lstadd_back(&tmp, ft_lstnew(buf[i]));
		i++;
	}
	return (tmp);
}

void	init(t_all *all, char **envi)
{
	all->env = init_lst_env_or_exp(envi);
	all->exp = init_lst_env_or_exp(envi);
	all->i = 0;
}
