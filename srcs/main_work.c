/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:18:39 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:18:44 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_buildins(t_list **env, t_list *exp, t_list *arg)
{
	if (!ft_strcmp(arg->val, "cd"))
		ft_cd(env, exp, arg);
	else if (!ft_strcmp(arg->val, "echo"))
		ft_echo(arg);
	else if (!ft_strcmp(arg->val, "env"))
		ft_env(*env);
	else if (!ft_strcmp(arg->val, "exit"))
		g_status = ft_exit(arg);
	else if (!ft_strcmp(arg->val, "export"))
		ft_export(env, exp, arg);
	else if (!ft_strcmp(arg->val, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(arg->val, "unset"))
		ft_unset(env, exp, arg);
	else
		return (1);
	return (0);
}

void	child(t_all *all, int all_i)
{
	char	**arg;
	char	**env;

	arg = from_lst_to_buf \
	(ft_lstsize(all->cmd[all_i]->arg), all->cmd[all_i]->arg, '\0');
	env = from_lst_to_buf(ft_lstsize(all->env), all->env, '\0');
	if (execve(all->cmd[all_i]->path_command, arg, env) == -1)
	{
		g_status = errno;
		exit(g_status);
	}
	exit(0);
}

static	int	binary(t_all *all)
{
	all->cmd[0]->pid = fork();
	if (all->cmd[0]->pid < 0)
	{
		g_status = errno;
		return (g_status);
	}
	if (all->cmd[0]->pid == 0)
	{
		child(all, 0);
		exit (g_status);
	}
	else
		waitpid(all->cmd[0]->pid, &g_status, 0);
	return (0);
}

int	main_work(t_all *all)
{
	ft_signal_in_child();
	if (!all->cmd[0]->arg)
		return (0); // нет команды, работаем дальше
	if (all->cmd[0]->type == BUILDIN)
	{
		if_buildins(&all->env, all->exp, all->cmd[0]->arg);
		return (g_status);
	}
	if (all->cmd[0]->type == BINARY)
		return (binary(all));
	return (0);
}
