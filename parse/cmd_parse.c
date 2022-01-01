/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:15:22 by sglossu           #+#    #+#             */
/*   Updated: 2022/01/01 18:59:22 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_cmd_struct(t_all *all, t_list *HEAD)
{
	int		i;
	t_list	*tmp;

	i = 0;
	free_path(all);
	while (i < all->number_command)
	{
		free_path(all);
		all->cmd[i]->arg = copy_part_of_list(all, HEAD, i);
		tmp = all->cmd[i]->arg;
		if (is_dir(tmp->val))
		{
			dir_parse(all->cmd[i]);
			tmp = tmp->next;
			if (!all->cmd[i]->name_file)
			{
				ft_putendl_fd(": syntax error near unexpected token `newline'",
					STDERR_FILENO);
				return (1);
			}
			else
				tmp = tmp->next;
		}
		if (tmp && is_buildin(tmp->val))
		{
			all->cmd[i]->path_command = NULL;
			all->cmd[i]->type = BUILDIN;
			all->cmd[i]->flag_redirect = false;
			all->cmd[i]->status = 0;
			dir_parse(all->cmd[i]);
		}
		else if (tmp && is_binary(tmp->val, all))
		{
			all->cmd[i]->type = BINARY;
			all->cmd[i]->status = 0;
			all->cmd[i]->flag_redirect = false;
			all->cmd[i]->path_command = path_com(all, tmp->val);
			if (!all->cmd[i]->path_command)
				return (error_return_int());
			dir_parse(all->cmd[i]);
			free_path(all);
		}
		i++;
	}
	return (0);
}

int	num_of_commands(t_all *all, t_list *HEAD)
{
	t_list	*tmp;
	int		res;
	int		flag;

	res = 0;
	flag = 0;
	tmp = HEAD;
	while (tmp)
	{
		if (tmp->flag == COMMAND || tmp->flag == WTF)
			res++;
		if (tmp->flag == WTF)
		{
			ft_printf(STDERR_FILENO, "minishell: %s: command not found\n",
				tmp->val);
			g_status = 127;
		}
		tmp = tmp->next;
	}
	all->number_command = res;
	return (flag);
}

int	init_cmd_struct(t_all *all)
{
	int		i;

	i = 0;
	all->cmd = malloc(sizeof(t_cmd *) * (all->number_command + 1));
	while (i < all->number_command)
	{
		all->cmd[i] = malloc(sizeof(t_cmd));
		all->cmd[i]->arg = NULL;
		all->cmd[i]->path_command = NULL;
		all->cmd[i]->name_file = NULL;
		all->cmd[i]->f_direct = 0;
		i++;
	}
	all->cmd[i] = NULL;
	return (0);
}

int	dir_parse(t_cmd *cmd)
{
	t_list		*tmp;
	int			dir_type;

	tmp = cmd->arg;
	while (tmp)
	{
		if (!ft_strcmp(tmp->val, ">"))
			dir_type = DIR;
		else if (!ft_strcmp(tmp->val, ">>"))
			dir_type = DOUB_DIR;
		else if (!ft_strcmp(tmp->val, "<"))
			dir_type = REDIR;
		else if (!ft_strcmp(tmp->val, "<<"))
			dir_type = DOUB_REDIR;
		else
			dir_type = NONE;
		if (dir_parse_help(tmp, cmd, dir_type))
			return (error_return_int());
		if (dir_type != NONE)
			return (0);
		tmp = tmp->next;
	}
	return (0);
}
