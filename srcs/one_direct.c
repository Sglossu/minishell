/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_direct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:18:49 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:18:55 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_rekurs_direct(t_cmd *cmd)
{
	combo_check(cmd);
	if (cmd->combo)
	{
		ft_lstremove(&cmd->arg, cmd->arg->next);
		ft_lstremove(&cmd->arg, cmd->arg->next);
		dir_parse(cmd);
		return (1);
	}
	ft_lstremove(&cmd->arg, cmd->arg->next);
	ft_lstremove(&cmd->arg, cmd->arg->next);
	dir_parse(cmd);
	return (0);
}

int	what_is_direct(t_all *all)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		g_status = errno;
		return (g_status);
	}
	if (all->cmd[all->i]->f_direct == DIR)
		ft_dir(all->cmd[all->i], STDOUT_FILENO);
	else if (all->cmd[all->i]->f_direct == DOUB_DIR)
		ft_doubledir(all->cmd[all->i], STDOUT_FILENO);
	else if (all->cmd[all->i]->f_direct == REDIR)
		ft_redir(all->cmd[all->i], STDIN_FILENO);
	else if (all->cmd[all->i]->f_direct == DOUB_REDIR)
	{
		ft_doubleredir(all->cmd[all->i], STDIN_FILENO, fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			g_status = errno;
			return (errno);
		}
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}	

int	main_function_for_one_direct(t_all *all)
{
	what_is_direct(all);
	if (check_for_rekurs_direct(all->cmd[all->i]))
	{
		main_function_for_one_direct(all);
	}
	what_is_direct(all);
	if (all->number_command == 1)
	{
		if (if_buildins(all, all->cmd[all->i]->arg))
			child(all, all->i);
	}
	return (0);
}

int	one_direct(t_all *all)
{
	int	status;

	all->cmd[all->i]->pid = fork();
	if (all->cmd[all->i]->pid == 0)
	{
		main_function_for_one_direct(all);
		exit(0);
	}
	else
	{
		waitpid(all->cmd[all->i]->pid, &status, 0);
	}
	return (0);
}
