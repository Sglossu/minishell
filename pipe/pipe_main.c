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

void	child_for_pipe(t_all *all, int com, int num_com, int **fd)
{
	int	i;
	(void)com;

	i = 0;
	if (num_com == 0)
		dup2(fd[num_com][1], STDOUT_FILENO); // первая команда
	else if (num_com == all->number_command - 1)
		dup2(fd[num_com - 1][0], STDIN_FILENO); // последняя
	else // пока это num_com = 1 // номер команды
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
	if (if_buildins(all, all->cmd[num_com]->arg))
		child(all, num_com);
	exit(g_status);
}

int	fork_and_close(t_all *all, int com, int **fd, int i)
{
	int	iserror;

	iserror = 0;
	while (i < com + 1)
	{
		all->cmd[i]->pid = fork();
		if (all->cmd[i]->pid < 0)
		{
			ft_printf(2, "fork failed: %s\n", strerror(errno));
			g_status = errno;
			iserror = 1;
			break ;
		}
		if (all->cmd[i]->pid == 0)
		{
			ft_signal_in_child();
			child_for_pipe(all, com, i, fd); // i - номер дочернего процесса, т. е. номер команды
			exit (g_status);
		}
		i++;
	}
	i = 0;
	while (i < com)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return (iserror);
}

int	pipe_for_another(t_all *all, int com) // com - количество пайпов
{
	int		**fd;
	int		i;

	fd = malloc(sizeof(int *) * com * 3);
	if (!fd)
	{
		g_status = errno;
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (g_status);
	}
	fd[com] = NULL;
	i = 0;
	while(i < com)
	{
		fd[i] = (int *)malloc(sizeof (int));
		if (!fd[i])
		{
			g_status = errno;
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return (g_status);
		}
		i++;
	}
	fd[i] = 0;
	i = 0;
	while (i < com)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			g_status = errno;
			return (errno);
		}
		i++;
	}
	i = 0;
	if (fork_and_close(all, com, fd, i))
	{
		ft_signal_main();
		return (g_status);
	}
	while (i < com + 1)
	{
		waitpid(all->cmd[i]->pid, &g_status, 0);
		i++;
	}
	ft_signal_main();
	return (0);
}

int	our_pipe(t_all *all)
{
	ft_signal_run_pipes();

	if (all->number_command == 2)
	{
		return (pipe_for_two(all));
	}
	else
	{
		return (pipe_for_another(all, all->number_command - 1));
	}
	return (0);
}

// env < 5 90 | ls > 8 9
