/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:15:22 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:15:27 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			all->cmd[i]->files = NULL;
			dir_parse(all->cmd[i]);
		}
		else if (is_binary(all->cmd[i]->arg->val, all))
		{
			all->cmd[i]->type = BINARY;
			all->cmd[i]->files = NULL;
			all->cmd[i]->path_command = path_com(all ,all->cmd[i]->arg->val); // потом когда-нибудь (никогда) добавить проверочку
			dir_parse(all->cmd[i]);
		}
		// printf("coomand number - %d\n", i+1);
		// ft_lstprint(all->cmd[i]->arg);
		// printf("f_direct status = %d\n", all->cmd[i]->f_direct);
		// printf("name_file = %s\n", all->cmd[i]->name_file);
		// ft_lstprint(all->cmd[i]->files);
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
		if (!ft_strcmp(tmp->val, "|") && tmp->flag == PIPE)
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

int dir_parse(t_cmd *cmd)
{
	t_list		*tmp;

	tmp = cmd->arg;

	while (tmp)
	{
		if (!ft_strcmp(tmp->val, ">"))
		{
			cmd->f_direct = DIR;
			ft_lstadd_back(&(cmd->files), tmp->next);
			return 0;
		}
		else if (!ft_strcmp(tmp->val, ">>"))
		{
			cmd->f_direct = DOUB_DIR;
			ft_lstadd_back(&(cmd->files), tmp->next);
			return 0;
		}
		else if (!ft_strcmp(tmp->val, "<"))
		{
			cmd->f_direct = REDIR;
			ft_lstadd_back(&(cmd->files), tmp->next);
			return 0;
		}
		else if (!ft_strcmp(tmp->val, "<<"))
		{
			cmd->f_direct = DOUB_REDIR;
			ft_lstadd_back(&(cmd->files), tmp->next);
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
	if (i > 1)
		cmd->combo = true;
	else
		cmd->combo = false;
}
