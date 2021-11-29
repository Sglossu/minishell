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

void	init(t_all *all, char **envi)
{
	int 	i = 0;

	all->env = init_lst_env(envi);
	all->cmd = malloc(sizeof(t_cmd *) * (all->number_command + 1));

	while(i < all->number_command)
	{
		all->cmd[i] = malloc(sizeof(t_cmd));
		i++;
	}
	all->cmd[i] = NULL;
	all->i = 0;
}
