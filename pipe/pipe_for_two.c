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

void	second_pipe(t_all *all, int fd[2])
{
	all->i = 1;
	all->cmd[1]->pid = fork();
	if (all->cmd[1]->pid < 0)
	{
		g_status = errno;
		ft_putendl_fd(strerror(errno), 2);
	}
	if (all->cmd[1]->pid == 0)
	{
		ft_signal_in_child();
		if (dup2(fd[0], STDIN_FILENO) == -1) // теперь stdin это как fd[0]
		{
			g_status = errno;
			exit(errno);
		}
		close(fd[1]);
		close(fd[0]);
		main_function_for_one_direct(all);
		if (if_buildins(all, all->cmd[all->i]->arg))
			child(all, 1);
		exit (g_status);
	}
}

void	first_pipe(t_all *all, int fd[2])
{
	all->cmd[0]->pid = fork();
	if (all->cmd[0]->pid < 0)
	{
		g_status = errno;
		ft_putendl_fd(strerror(errno), 2);
	}
	if (all->cmd[0]->pid == 0)
	{
		ft_signal_in_child();
		if (dup2(fd[1], STDOUT_FILENO) == -1) // делает stdout (вывод) копией fd[1], теперь stdout это как fd[1]
		{
			g_status = errno;
			exit(errno);
		}
		close(fd[0]);
		close(fd[1]);
		main_function_for_one_direct(all);
		if (if_buildins(all, all->cmd[0]->arg))
			child(all, 0);
		exit(g_status);
	}
}

int	pipe_for_two(t_all *all)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		g_status = errno;
		return (errno);
	}
	first_pipe(all, fd);
	second_pipe(all, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(all->cmd[0]->pid, &g_status, 0);
	waitpid(all->cmd[1]->pid, &g_status, 0);
	ft_signal_main();
	return (0);
}
