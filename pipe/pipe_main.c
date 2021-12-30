/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:17:58 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:18:04 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_for_pipe(t_all *all, int num_com, int **fd)
{
	int	i;

	i = 0;
	if (num_com == 0)
		dup2(fd[num_com][1], STDOUT_FILENO);
	else if (num_com == all->number_command - 1)
		dup2(fd[num_com - 1][0], STDIN_FILENO);
	else
	{
		dup2(fd[num_com - 1][0], STDIN_FILENO);
		dup2(fd[num_com][1], STDOUT_FILENO);
	}
	all->i = num_com;
	if (all->cmd[num_com]->f_direct != NONE)
		main_function_for_one_direct(all);
	while (i < all->number_command - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	if (all->cmd[num_com]->arg && if_buildins(all, all->cmd[num_com]->arg))
		child(all, num_com);
	exit(g_status);
}

static	void	error_fork(void)
{
	ft_printf(2, "fork failed: %s\n", strerror(errno));
	g_status = errno;
}

int	fork_and_close(t_all *all, int com, int **fd, int i)
{
	g_status = 0;
	while (i < com + 1)
	{
		all->cmd[i]->pid = fork();
		if (all->cmd[i]->pid < 0)
		{
			error_fork();
			break ;
		}
		if (all->cmd[i]->pid == 0)
		{
			ft_signal_in_child();
			child_for_pipe(all, i, fd);
			exit (g_status);
		}
		i++;
	}
	i = -1;
	while (++i < com)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	ft_signal_main();
	return (g_status);
}

int	our_pipe(t_all *all)
{
	ft_signal_run_pipes();
	if (all->number_command == 2)
	{
		return (pipe_for_two(all));
	}
	return (pipe_for_another(all, all->number_command - 1));
}
