/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_for_another.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:05:45 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/27 14:05:47 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	**memory_for_fd(int com, int i)
{
	int	**fd;

	fd = malloc(sizeof(int *) * com * 3);
	if (!fd)
	{
		g_status = errno;
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		ft_signal_main();
		return (NULL);
	}
	fd[com] = NULL;
	while (++i < com)
	{
		fd[i] = (int *)malloc(sizeof (int));
		if (!fd[i])
		{
			g_status = errno;
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			ft_signal_main();
			return (NULL);
		}
	}
	fd[i] = 0;
	return (fd);
}

static	int	pipes_for_all_com(int com, int **fd)
{
	int	i;

	i = -1;
	while (++i < com)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			ft_signal_main();
			g_status = errno;
			return (g_status);
		}
	}
	return (0);
}

int	pipe_for_another(t_all *all, int com) // com - количество пайпов
{
	int		**fd;
	int		i;

	fd = memory_for_fd(com, -1);
	if (!fd)
		return (g_status);
	if (pipes_for_all_com(com, fd))
		return (g_status);
	i = -1;
	if (fork_and_close(all, com, fd, 0))
	{
		while (++i <= com)
			free(fd[i]);
		free(fd);
		ft_signal_main();
		return (g_status);
	}
	while (++i < com + 1)
		waitpid(all->cmd[i]->pid, &g_status, 0);
	i = -1;
	while (++i <= com)
		free(fd[i]);
	free(fd);
	ft_signal_main();
	return (0);
}