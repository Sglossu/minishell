/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:15:22 by sglossu           #+#    #+#             */
/*   Updated: 2022/01/02 00:56:40 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	return_cmd(void)
{
	ft_putendl_fd(": syntax error near unexpected token `newline'",
		STDERR_FILENO);
	return (1);
}

int	fill_cmd_struct(t_all *all, t_list *HEAD)
{
	int		i;
	t_list	*tmp;

	i = -1;
	free_path(all);
	while (++i < all->number_command)
	{
		free_path(all);
		if (!all->cmd)
			return (g_status);
		all->cmd[i]->arg = copy_part_of_list(all, HEAD, i);
		tmp = all->cmd[i]->arg;
		if (is_dir(tmp->val))
		{
			dir_parse(all->cmd[i]);
			tmp = tmp->next;
			if (!all->cmd[i]->name_file)
				return_cmd();
			else
				tmp = tmp->next;
		}
		if (fill_cmd_struct_help(all, all->cmd[i], tmp))
			return (error_return_int());
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
		if (is_wtf(all, tmp))
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
	if (!all->cmd)
		return (error_return_int());
	while (i < all->number_command)
	{
		all->cmd[i] = malloc(sizeof(t_cmd));
		if (!all->cmd[i])
		{
			ft_free(all);
			return (error_return_int());
		}
		all->cmd[i]->arg = NULL;
		all->cmd[i]->path_command = NULL;
		all->cmd[i]->name_file = NULL;
		all->cmd[i]->f_direct = NONE;
		i++;
	}
	all->cmd[i] = NULL;
	return (0);
}
