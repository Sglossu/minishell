/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function_for_one_direct.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:44:53 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/27 19:44:56 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	how_much_doub_redir(t_all *all)
{
	t_list	*tmp;

	all->count_doub_redir = 0;
	tmp = all->cmd[all->i]->arg;
	while (tmp)
	{
		if (!ft_strcmp((tmp->val), "<<"))
			all->count_doub_redir++;
		tmp = tmp->next;
	}
}

int	execute_and_delete_redir(t_all *all)
{
	t_cmd	*tmp;
	t_list	*tmp2_del;
	t_list	*tmp3_del;
	char	*str;

	tmp = all->cmd[all->i];
	while (tmp->name_file && tmp->f_direct != NONE)
	{
		what_is_direct(all);
		str = direct_for_lstfind(all->cmd[all->i]);
		if (!str)
			return (error_return_int());
		tmp2_del = ft_lstfind(tmp->arg, str);
		tmp3_del = tmp2_del->next;
		ft_lstremove(&all->cmd[all->i]->arg, tmp2_del);
		ft_lstremove(&all->cmd[all->i]->arg, tmp3_del);
		free(all->cmd[all->i]->name_file);
		all->cmd[all->i]->name_file = NULL;
		all->cmd[all->i]->f_direct = NONE;
		dir_parse(all->cmd[all->i]);
	}
	return (0);
}

int	main_function_for_one_direct(t_all *all)
{
	how_much_doub_redir(all);
	if (all->count_doub_redir)
		execute_double_redir(all);
	if (execute_and_delete_redir(all))
		return (1);
	if (!all->cmd[all->i]->arg)
		return (g_status);
	if (all->number_command == 1)
	{
		if (if_buildins(all, all->cmd[all->i]->arg))
			child(all, all->i);
		if (g_status)
			return (g_status);
	}
	if (g_status)
		return (g_status);
	return (0);
}
