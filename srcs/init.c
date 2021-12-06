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
	all->number_command = 1; // потом убрать, когда научимся считать количество комманд
	int 	i = 0;

	all->env = init_lst_env(envi);
	all->cmd = malloc(sizeof(t_cmd *) * (all->number_command + 1));

	while(i < all->number_command)
	{
		all->cmd[i] = malloc(sizeof(t_cmd));
<<<<<<< HEAD
		all->cmd[i]->name_file = NULL;
		all->cmd[i]->f_direct = NONE;
=======
		all->cmd[i]->f_direct = NONE;
		all->cmd[i]->name_file = NULL;
		all->cmd[i]->path_command = NULL;
>>>>>>> 973fa81f5b1b4ed802e81d0bcbe10ff5ba864eb5
		i++;
	}
	all->cmd[i] = NULL;
	all->i = 0;
}
