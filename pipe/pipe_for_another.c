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

	fd = malloc(sizeof(int *) * (com + 1));
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
		fd[i] = (int *)malloc(sizeof (int) * 3);
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

static	int	pipes_for_all_com(t_all *all, int com, int **fd)
{
	int	i;

	(void)com;
	i = -1;
	while (++i < all->number_command - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			fd_close(i - 1, fd);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			ft_signal_main();
			g_status = errno;
			free_fd(all, fd);
			return (g_status);
		}
	}
	return (0);
}

static	void	ft_waitpid(t_all *all, int com)
{
	all->i = -1;
	while (++all->i < com + 1)
	{
		waitpid(all->cmd[all->i]->pid, &all->cmd[all->i]->status, 0);
		g_status = WEXITSTATUS(all->cmd[all->i]->status);
		if (!g_status && WIFSIGNALED(all->cmd[all->i]->status))
		{
			if (all->cmd[all->i]->status == 2 || all->cmd[all->i]->status == 3)
				ft_putendl_fd("", 2);
			g_status = 128 + WTERMSIG(all->cmd[all->i]->status);
		}
	}
}

int	pipe_for_another(t_all *all, int com)
{
	int		**fd;
	int		i;

	fd = memory_for_fd(com, -1);
	if (!fd)
		return (g_status);
	if (pipes_for_all_com(all, com, fd))
		return (g_status);
	i = -1;
	if (fork_and_close(all, com, fd, -1))
	{
		while (++i <= com)
			free(fd[i]);
		free(fd);
		ft_signal_main();
		return (g_status);
	}
	ft_waitpid(all, com);
	i = -1;
	while (++i <= com)
		free(fd[i]);
	free(fd);
	ft_signal_main();
	return (0);
}
