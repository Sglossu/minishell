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
		ft_cd(env, arg);
	else if (!ft_strcmp(arg->val, "echo"))
		ft_echo(arg);
	else if (!ft_strcmp(arg->val, "env"))
		ft_env(*env);
	else if (!ft_strcmp(arg->val, "exit"))
		s_status = ft_exit(arg);
	else if (!ft_strcmp(arg->val, "export"))
		ft_export(env, exp, arg);
	else if (!ft_strcmp(arg->val, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(arg->val, "unset"))
		ft_unset(env, exp, arg);
	else
		return (1);
	return(0);
}

void	child(t_all *all, int all_i)
{
	char	**arg;
	char	**env;

	arg = from_lst_to_buf(ft_lstsize(all->cmd[all_i]->arg), all->cmd[all_i]->arg, '\0');
	env = from_lst_to_buf(ft_lstsize(all->env), all->env, '\0');
	if (execve(all->cmd[all_i]->path_command, arg, env) == -1)
	{
		s_status = errno;
		exit(s_status);
	}
	exit(0);
}

int	main_work(t_all *all)
{
	int i = all->i;

	ft_signal_in_child();

	if (!all->cmd[i]->arg)
		return (0); // нет команды, работаем дальше
	
	if (all->cmd[i]->type == BUILDIN)
	{
		if_buildins(&all->env, all->exp, all->cmd[i]->arg);
		return (s_status);
	}
	if (all->cmd[i]->type == BINARY)
	{
		all->cmd[i]->pid = fork();
		if (all->cmd[i]->pid < 0)
		{
			s_status = errno;
			return(s_status);
		}
		if (all->cmd[i]->pid == 0)
		{
			child(all, 0);
			exit (s_status);
		}
		else
			waitpid(all->cmd[i]->pid, &s_status, 0);
	}
	return (1);
}
