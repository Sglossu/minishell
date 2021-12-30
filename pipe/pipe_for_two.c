/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_for_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:32:35 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:32:37 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	second_pipe(t_all *all, int fd[2])
{
	all->i = 1;
	all->cmd[1]->pid = fork();
	if (all->cmd[1]->pid == -1)
	{
		ft_printf(2, "fork failed: %s\n", strerror(errno));
		g_status = errno;
		return (1);
	}
	if (all->cmd[1]->pid == 0)
	{
		ft_signal_in_child();
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			g_status = errno;
			exit(errno);
		}
		close(fd[1]);
		close(fd[0]);
		main_function_for_one_direct(all);
		if (all->cmd[all->i]->arg && if_buildins(all, all->cmd[all->i]->arg))
			child(all, all->i);
		exit (g_status);
	}
	return (0);
}

int	first_pipe(t_all *all, int fd[2])
{
	all->cmd[0]->pid = fork();
	if (all->cmd[1]->pid == -1)
	{
		ft_printf(2, "fork failed: %s\n", strerror(errno));
		g_status = errno;
		return (1);
	}
	if (all->cmd[0]->pid == 0)
	{
		ft_signal_in_child();
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			g_status = errno;
			exit(errno);
		}
		close(fd[0]);
		close(fd[1]);
		main_function_for_one_direct(all);
		if (all->cmd[all->i]->arg && if_buildins(all, all->cmd[all->i]->arg))
			child(all, all->i);
		exit(g_status);
	}
	return (0);
}

int	pipe_for_two(t_all *all)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		g_status = errno;
		return (errno);
	}
	if (first_pipe(all, fd))
		return (1);
	if (second_pipe(all, fd))
		return (1);
	close(fd[0]);
	close(fd[1]);
	all->i = -1;
	while (++all->i < 2)
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
//	ft_printf(2, "g_status: %d\n", g_status);
//	waitpid(all->cmd[1]->pid, &g_status, 0);
//	ft_printf(2, "g_status: %d\n", g_status);

	ft_signal_main();
	return (0);
}
