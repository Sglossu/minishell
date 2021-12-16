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

void	child_for_pipe(t_all *all, int num_com, int fd[2][2])
{
	int i = 0;

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
	if (if_buildins(&all->env, all->exp, all->cmd[num_com]->arg))
		child(all, num_com);
	exit(s_status);
}

int pipe_for_another(t_all *all, int com, int *status) // com - количество пайпов
{
	int 	fd[com][2];
	pid_t	pid[com + 1];
	int 	i = 0;

	while (i < com)
	{
		if (pipe(fd[i]) == -1)
			return (1); // todo обработать ошибку
		i++;
	}
	i = 0;
	while (i < com + 1)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			ft_signal_in_child();
			child_for_pipe(all, i, fd); // i - номер дочернего процесса, т. е. номер команды
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
	i = 0;
	while (i < com + 1)
	{
		waitpid(pid[i], status, 0);
		i++;
	}
	ft_signal_main();
	return (0);
}

int pipe_for_two(t_all *all, int *status)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		return (1); // todo обработать ошибку
	pid[0] = fork();
	if (pid[0] < 0)
		return (2); // todo обработать ошибку
	if (pid[0] == 0)
	{
		ft_signal_in_child();
		dup2(fd[1], STDOUT_FILENO); // делает stdout (вывод) копией fd[1], теперь stdout это как fd[1]
		close(fd[0]);
		close(fd[1]);
		main_function_for_one_direct(all);
		if (if_buildins(&all->env, all->exp, all->cmd[0]->arg))
			child(all, 0);
		exit(s_status);
	}
	pid[1] = fork();
	all->i = 1;
	if (pid[1] < 0)
		return (3); // todo обработать ошибку
	if (pid[1] == 0)
	{
		ft_signal_in_child();
		dup2(fd[0], STDIN_FILENO); // теперь stdin (ввод) это как fd[0]
		close(fd[1]);
		close(fd[0]);
		main_function_for_one_direct(all);
		if (if_buildins(&all->env, all->exp, all->cmd[all->i]->arg))
			child(all, 1);
		exit (s_status);
	}
	close(fd[0]);
	close(fd[1]);

	waitpid(pid[0], status, 0);
	waitpid(pid[1], status, 0);
	ft_signal_main();
	return (0);
}

int our_pipe(t_all *all)
{
	int status = 0;
	ft_signal_run_pipes();
	if (all->number_command == 2)
	{
		return(pipe_for_two(all, &status));
	}
	else
	{
		return(pipe_for_another(all, all->number_command - 1, &status));
	}
	return (0);
}
