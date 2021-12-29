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
	t_cmd	*tmp;
	t_list	*tmp2_del;
	t_list	*tmp3_del;
	char	*str;

	tmp = all->cmd[all->i];
	while (tmp->arg)
	{
		if (!ft_strcmp(tmp->arg->val, "<<"))
		{
			tmp->f_direct = DOUB_REDIR;
			if (tmp->arg->next)
				tmp->name_file = ft_strdup(tmp->arg->next->val);
			if (!tmp->name_file)
				return (error_return_nothing());

			what_is_direct(all);
			str = direct_for_lstfind(tmp);
			if (!str)
				return (error_return_nothing());
			tmp2_del = ft_lstfind(tmp->arg, str);
			tmp3_del = tmp2_del->next;
			ft_lstremove(&tmp->arg, tmp2_del);
			ft_lstremove(&tmp->arg, tmp3_del);
			free(tmp->name_file);
			tmp->name_file = NULL;
			tmp->f_direct = NONE;
		}
		if (tmp->arg)
			tmp->arg = tmp->arg->next;
//		else
//			break ;
	}
}
