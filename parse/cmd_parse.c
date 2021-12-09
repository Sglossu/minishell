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
			dir_parse(all->cmd[i]);
		}
		else if (is_binary(all->cmd[i]->arg->val, all))
		{
			all->cmd[i]->type = BINARY;
			all->cmd[i]->path_command = path_com(all ,all->cmd[i]->arg->val);
			if (!(all->cmd[i]->path_command))
				{
					printf("ВНИМАНИЕ! ПРОИЗОШЛА ЧУШЬ!\n");
					exit(777);
				}
			dir_parse(all->cmd[i]);
		}
		printf("coomand number - %d\n", i+1);
		ft_lstprint(all->cmd[i]->arg);
		printf("f_direct status = %d\n", all->cmd[i]->f_direct);
		printf("name_file = %s\n", all->cmd[i]->name_file);
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

int dir_parse(t_cmd *cmd)
{
	t_list *tmp;

	if (ft_lstfind(cmd->arg, ">"))
	{
		cmd->f_direct = DIR;
		tmp = ft_lstfind(cmd->arg, ">");
  	}
	else if (ft_lstfind(cmd->arg, ">>"))
	{
		cmd->f_direct = DOUB_DIR;
		tmp = ft_lstfind(cmd->arg, ">>");
	}
	else if (ft_lstfind(cmd->arg, "<"))
	{
		cmd->f_direct = REDIR;
		tmp = ft_lstfind(cmd->arg, "<");	
	}
	else if (ft_lstfind(cmd->arg, "<<"))
	{
		cmd->f_direct = DOUB_REDIR;
		tmp = ft_lstfind(cmd->arg, "<<");
	}
	else
		cmd->f_direct = NONE;
	if (cmd->f_direct != NONE)
	{
		tmp = tmp->next;
		cmd->name_file = tmp->val;
	}
	return 0;
}