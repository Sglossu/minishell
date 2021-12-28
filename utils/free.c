/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:17:03 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:17:05 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_path(t_all *all)
{
	int i;

	i = -1;
	while (all->path && all->path[++i])
		free(all->path[i]);
	free(all->path);
	all->path = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	ft_lstclear(&cmd->arg, free);
	if (cmd->path_command)
	{
		free(cmd->path_command);
		cmd->path_command = NULL;
	}
	if (cmd->name_file)
	{
		free(cmd->name_file);
		cmd->name_file = NULL;
	}
}

int	ft_free(t_all *all)
{
	int	i;

	i = -1;
	while (all->cmd[++i])
		free_cmd(all->cmd[i]);
//	free(all->cmd);
//	all->cmd = NULL;
//	free_path(all);

	all->number_command = 0;
	all->i = 0;
	return (0);
}
