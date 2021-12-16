#include "../includes/minishell.h"

int	fill_cmd_struct(t_all *all, t_list *HEAD)
{
	int		i;
	i = 0;

	while (all->cmd[i])
	{

		all->cmd[i]->arg = copy_part_of_list(all, HEAD, i);
		combo_check(all->cmd[i]);
		if (is_buildin(all->cmd[i]->arg->val))
		{
			all->cmd[i]->path_command = NULL;
			all->cmd[i]->type = BUILDIN;
			dir_parse(all->cmd[i]);
		}
		else if (is_binary(all->cmd[i]->arg->val, all))
		{
			all->cmd[i]->type = BINARY;
			all->cmd[i]->path_command = path_com(all ,all->cmd[i]->arg->val); // потом когда-нибудь (никогда) добавить проверочку
			dir_parse(all->cmd[i]);
		}
		// printf("coomand number - %d\n", i+1);
		// ft_lstprint(all->cmd[i]->arg);
		// printf("f_direct status = %d\n", all->cmd[i]->f_direct);
		// printf("name_file = %s\n", all->cmd[i]->name_file);
		// printf("path_command = %s\n", all->cmd[i]->path_command);
		i++;		
	}
	return 0;
}

void	num_of_commands(t_all *all, t_list *HEAD)
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
	all->number_command = res;
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
	t_list		*tmp;

	tmp = cmd->arg;

	while (tmp)
	{
		if (!ft_strcmp(tmp->val, ">"))
		{
			cmd->f_direct = DIR;
			cmd->name_file = ft_strdup(tmp->next->val);
			ft_lstremove(&cmd->arg, cmd->arg->next);
			ft_lstremove(&cmd->arg, cmd->arg->next);
			// ft_putendl_fd(cmd->name_file,2);
			// ft_putnbr_fd(cmd->f_direct, 2);
			return 0;
		}
		else if (!ft_strcmp(tmp->val, ">>"))
		{
			cmd->f_direct = DOUB_DIR;
			cmd->name_file = ft_strdup(tmp->next->val);
			ft_lstremove(&cmd->arg, cmd->arg->next);
			ft_lstremove(&cmd->arg, cmd->arg->next);
			// ft_putendl_fd(cmd->name_file,2);
			// ft_putnbr_fd(cmd->f_direct, 2);
			return 0;
		}
		else if (!ft_strcmp(tmp->val, "<"))
		{
			cmd->f_direct = REDIR;
			cmd->name_file = ft_strdup(tmp->next->val);
			ft_lstremove(&cmd->arg, cmd->arg->next);
			ft_lstremove(&cmd->arg, cmd->arg->next);
			// ft_putendl_fd(cmd->name_file,2);
			// ft_putnbr_fd(cmd->f_direct, 2);
			return 0;
		}
		else if (!ft_strcmp(tmp->val, "<<"))
		{
			cmd->f_direct = DOUB_REDIR;
			cmd->name_file = ft_strdup(tmp->next->val);
			ft_lstremove(&cmd->arg, cmd->arg->next);
			ft_lstremove(&cmd->arg, cmd->arg->next);
			// ft_putendl_fd(cmd->name_file,2);
			// ft_putnbr_fd(cmd->f_direct, 2);
			return 0;
		}
		else
		{
			cmd->f_direct = NONE;
			cmd->name_file = NULL;
		}
		tmp = tmp->next;
	}
	return 1;
}

void combo_check(t_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = cmd->arg;
	while (tmp)
	{
		if ((!ft_strcmp(tmp->val, "<")) || (!ft_strcmp(tmp->val, "<<"))
				|| (!ft_strcmp(tmp->val, ">")) || (!ft_strcmp(tmp->val, ">>")))
				i++;
		tmp = tmp->next;
	}
	if (i > 2)
		cmd->combo = true;
	else
		cmd->combo = false;
}