/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 00:56:03 by bshawn            #+#    #+#             */
/*   Updated: 2022/01/02 00:59:42 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dir_parse(t_cmd *cmd)
{
	t_list	*tmp;
	tmp = cmd->arg;
	while (tmp)
	{
		if (!ft_strcmp(tmp->val, ">"))
		{
			cmd->f_direct = DIR;
			if (tmp->next)
				cmd->name_file = ft_strdup(tmp->next->val);
			if (!cmd->name_file)
				return (error_return_int());
			return (0);
		}
		else if (!ft_strcmp(tmp->val, ">>"))
		{
			cmd->f_direct = DOUB_DIR;
			if (tmp->next)
				cmd->name_file = ft_strdup(tmp->next->val);
			if (!cmd->name_file)
				return (error_return_int());
			return (0);
		}
		else if (!ft_strcmp(tmp->val, "<"))
		{
			cmd->f_direct = REDIR;
			if (tmp->next)
				cmd->name_file = ft_strdup(tmp->next->val);
			if (!cmd->name_file)
				return (error_return_int());
			return (0);
		}
		else if (!ft_strcmp(tmp->val, "<<"))
		{
			cmd->f_direct = DOUB_REDIR;
			if (tmp->next)
				cmd->name_file = ft_strdup(tmp->next->val);
			if (!cmd->name_file)
				return (error_return_int());
			return (0);
		}
		else
		{
			cmd->f_direct = NONE;
			cmd->name_file = NULL;
		}
		tmp = tmp->next;
	}
	return (1);
}