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
			close(fd[0]);
			close(fd[1]);
			g_status = errno;
			return (errno);
		}
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
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

int	main_function_for_one_direct(t_all *all)
{
	t_cmd	*tmp;
	t_list	*tmp2_del;
	t_list	*tmp3_del;
	char 	*str;

	tmp = all->cmd[all->i];
	while (tmp->name_file && tmp->f_direct)
	{
		what_is_direct(all);
		str = direct_for_lstfind(all->cmd[all->i]);
		if (!str)
			return (1);
		tmp2_del = ft_lstfind(tmp->arg, str);
		tmp3_del = tmp2_del->next;
		ft_lstremove(&all->cmd[all->i]->arg, tmp2_del);
		ft_lstremove(&all->cmd[all->i]->arg, tmp3_del);

		free(all->cmd[all->i]->name_file);
		all->cmd[all->i]->name_file = NULL;
		all->cmd[all->i]->f_direct = 0;

		dir_parse(all->cmd[all->i]);
	}
	if (all->number_command == 1)
	{
		if (g_status)
			return (g_status);
		if (if_buildins(all, all->cmd[all->i]->arg))
			child(all, all->i);
	}
	return (0);
}

int	one_direct(t_all *all)
{

//	main_function_for_one_direct(all);
//	exit (0);

	int	status;

	all->cmd[all->i]->pid = fork();
	if (all->cmd[all->i]->pid == -1)
	{
		g_status = errno;
		ft_printf(2, "fork failed: %s\n", strerror(errno));
		return (g_status);
	}
	if (all->cmd[all->i]->pid == 0)
	{
		redirect_in_start(all);
		main_function_for_one_direct(all);
		exit(0);
	}
	else
	{
		waitpid(all->cmd[all->i]->pid, &status, 0); // выводить печать статуса если ошибка?
	}
	return (0); // что возвращать если несколько команд?
}
