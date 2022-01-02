/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 00:56:03 by bshawn            #+#    #+#             */
/*   Updated: 2022/01/02 01:31:24 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	dir(t_cmd *cmd, t_list *tmp)
{
	cmd->f_direct = DIR;
	if (tmp->next)
		cmd->name_file = ft_strdup(tmp->next->val);
	if (!cmd->name_file)
		return (error_return_int());
	return (0);
}

static int	doub_dir(t_cmd *cmd, t_list *tmp)
{
	cmd->f_direct = DOUB_DIR;
	if (tmp->next)
		cmd->name_file = ft_strdup(tmp->next->val);
	if (!cmd->name_file)
		return (error_return_int());
	return (0);
}

static int redir(t_cmd *cmd, t_list *tmp)
{
	cmd->f_direct = REDIR;
	if (tmp->next)
		cmd->name_file = ft_strdup(tmp->next->val);
	if (!cmd->name_file)
		return (error_return_int());
	return (0);
}

static int doub_redir(t_cmd *cmd, t_list *tmp)
{
	cmd->f_direct = DOUB_REDIR;
	if (tmp->next)
		cmd->name_file = ft_strdup(tmp->next->val);
	if (!cmd->name_file)
		return (error_return_int());
	return (0);
}

int	dir_parse(t_cmd *cmd)
{
	t_list	*tmp;
	tmp = cmd->arg;
	while (tmp)
	{
		if (!ft_strcmp(tmp->val, ">"))
			return (dir(cmd, tmp));
		else if (!ft_strcmp(tmp->val, ">>"))
			return (doub_dir(cmd, tmp));
		else if (!ft_strcmp(tmp->val, "<"))
			return (redir(cmd, tmp));
		else if (!ft_strcmp(tmp->val, "<<"))
			return (doub_redir(cmd, tmp));
		else
		{
			cmd->f_direct = NONE;
			cmd->name_file = NULL;
		}
		tmp = tmp->next;
	}
	return (1);
}