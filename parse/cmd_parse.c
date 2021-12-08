#include "../includes/minishell.h"

int	fill_cmd_struct(t_all *all, t_list *HEAD)
{
	int		i;
	i = 0;

	while (all->cmd[i])
	{ 
		all->cmd[i]->arg = copy_part_of_list(all, HEAD, i);
		if (is_buildin(all->cmd[i]->arg->val))
		{
			all->cmd[i]->path_command = NULL;
			all->cmd[i]->f_direct = NONE;
			all->cmd[i]->type = BUILDIN;
		}
		else if (is_binary(all->cmd[i]->arg->val, all))
		{
			all->cmd[i]->path_command = path_com(all ,all->cmd[i]->arg->val);
			if (!(all->cmd[i]->path_command))
				{
					printf("ВНИМАНИЕ! ПРОИЗОШЛА ЧУШЬ!\n");
					exit(777);
				}
			all->cmd[i]->type = BINARY;
			all->cmd[i]->f_direct = NONE;
		}
		i++;		
	}
	return 0;
}

int	num_of_commands(t_list *HEAD, t_all *all)
{
	int		res;
	t_list	*tmp;
	int		pipes;

	res = 0;
	pipes = 1;
	parse_path(all);
	tmp = HEAD;
	while (tmp)
	{
		if ((is_buildin(tmp->val) || is_binary(tmp->val, all)) && pipes)
		{
			res++;
			pipes = 0;
		}
		if (!ft_strcmp(tmp->val, "|"))
			pipes = 1;
		tmp = tmp->next;
	}
	return res;
}

int	init_cmd_struct(t_all *all)
{
	int		i;

	i = 0;
	all->cmd = malloc(sizeof(t_cmd *) * (all->number_command + 1));
	while(i < all->number_command)
	{
		all->cmd[i] = malloc(sizeof(t_cmd));
		i++;
	}
	all->cmd[i] = NULL;
	return (0); 
}

char *path_com(t_all *all, char *command)
{
	int i = 0;
	parse_path(all);
	path_pl_command(all, command);

	while (all->path[i])
	{
		if (!access(all->path[i], 0 | 1))
		{
			return (all->path[i]); // команда нашлась по этому пути
		}
		i++;
	}
	return (NULL);
}