/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:17:03 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/29 19:47:43 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_path(t_all *all)
{
	int	i;

	i = -1;
	if (!all->path)
		return ;
	while (all->path && all->path[++i])
		free(all->path[i]);
	free(all->path);
	all->path = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd && cmd->arg)
		ft_lstclear(&cmd->arg, free);
	if (cmd && cmd->path_command)
	{
		free(cmd->path_command);
		cmd->path_command = NULL;
	}
	if (cmd && cmd->name_file)
	{
		free(cmd->name_file);
		cmd->name_file = NULL;
	}
}

void	free_fd(t_all *all, int **fd)
{
	int		i;

	(void)all;
	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	ft_free(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->number_command)
	{
		free_cmd(all->cmd[i]);
		free(all->cmd[i]);
		i++;
	}
	free(all->cmd);
	all->cmd = NULL;
	all->number_command = 0;
	all->path = NULL;
	all->i = 0;
	return (0);
}
