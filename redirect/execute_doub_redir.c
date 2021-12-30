/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_doub_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 22:23:21 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/29 22:23:23 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_double_redir(t_all *all)
{
	t_list	*tmp;
	t_list	*tmp2_del;
	t_list	*tmp3_del;
	char	*str;

	tmp = all->cmd[all->i]->arg;
	while (tmp)
	{
		if (!ft_strcmp(tmp->val, "<<"))
		{
			all->cmd[all->i]->f_direct = DOUB_REDIR;
			if (tmp->next)
				all->cmd[all->i]->name_file = ft_strdup(tmp->next->val);
			if (!all->cmd[all->i]->name_file)
				return (error_return_nothing());

			what_is_direct(all);
			str = ft_strdup("<<");
			if (!str)
				return (error_return_nothing());
			tmp2_del = ft_lstfind(tmp, str);
			tmp3_del = tmp2_del->next; // сделать if
			ft_lstremove(&all->cmd[all->i]->arg, tmp2_del);
			ft_lstremove(&all->cmd[all->i]->arg, tmp3_del);
			free(all->cmd[all->i]->name_file);
			all->cmd[all->i]->name_file = NULL;
			all->cmd[all->i]->f_direct = NONE;
		}
		if (tmp)
			tmp = tmp->next;
//		else
//			break ;
	}
}
