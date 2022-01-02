/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_direct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:18:49 by sglossu           #+#    #+#             */
/*   Updated: 2022/01/02 14:58:48 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	close_fd(int fd_0, int fd_1)
{
	close(fd_0);
	close(fd_1);
	return (0);
}

int	what_is_direct(t_all *all)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_return_int();
	if (all->cmd[all->i]->f_direct == DIR)
		ft_dir(all->cmd[all->i], STDOUT_FILENO);
	else if (all->cmd[all->i]->f_direct == DOUB_DIR)
		ft_doubledir(all->cmd[all->i], STDOUT_FILENO);
	else if (all->cmd[all->i]->f_direct == REDIR)
		ft_redir(all->cmd[all->i], STDIN_FILENO);
	else if (all->cmd[all->i]->f_direct == DOUB_REDIR)
	{
		ft_doubleredir(all->cmd[all->i], STDIN_FILENO, fd[1]);
		if (all->count_doub_redir > 1)
		{
			all->count_doub_redir--;
			return (close_fd(fd[0], fd[1]));
		}
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			close_fd(fd[0], fd[1]);
			error_return_int();
		}
	}
	return (close_fd(fd[0], fd[1]));
}	

char	*direct_for_lstfind(t_cmd *cmd)
{
	char	*str;

	str = NULL;
	if (cmd->f_direct == DIR)
		str = ft_strdup(">");
	else if (cmd->f_direct == REDIR)
		str = ft_strdup("<");
	else if (cmd->f_direct == DOUB_REDIR)
		str = ft_strdup("<<");
	else if (cmd->f_direct == DOUB_DIR)
		str = ft_strdup(">>");
	if (!str)
	{
		g_status = errno;
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (NULL);
	}
	return (str);
}

int	one_direct(t_all *all)
{
	all->cmd[all->i]->pid = fork();
	if (all->cmd[all->i]->pid == -1)
	{
		g_status = errno;
		ft_printf(2, "fork failed: %s\n", strerror(errno));
		return (g_status);
	}
	if (all->cmd[all->i]->pid == 0)
	{
		main_function_for_one_direct(all);
		exit(g_status);
	}
	else
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
	return (0);
}
