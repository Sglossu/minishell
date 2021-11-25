//
// Created by Shasta Glossu on 11/20/21.
//

#include "../includes/minishell.h"

t_list	*init_lst_env(char **envi)
{
	t_list	*envp_l;
	int		i;

	envp_l = NULL;
	i = 0;
	while (envi[i])
	{
		ft_lstadd_back(&envp_l, ft_lstnew(envi[i]));
		i++;
	}
	return (envp_l);
}

void	init(t_all **all, char **envi)
{
	(*all)->arg = NULL;
	(*all)->env = init_lst_env(envi);
}
