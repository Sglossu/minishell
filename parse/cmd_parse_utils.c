/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:21:55 by bshawn            #+#    #+#             */
/*   Updated: 2022/01/01 23:10:05 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dir_parse_help(t_list *tmp, t_cmd *cmd, int dir_type)
{
	cmd->f_direct = dir_type;
	if (tmp->next)
	{
		cmd->name_file = ft_strdup(tmp->next->val);
		if (!cmd->name_file)
			return (error_return_int());
	}
	return (0);
}

int	fill_cmd_struct_help(t_all *all, t_cmd *cmd, t_list *tmp)
{
	if (tmp && is_buildin(tmp->val))
	{
		cmd->path_command = NULL;
		cmd->type = BUILDIN;
		cmd->flag_redirect = false;
		cmd->status = 0;
		dir_parse(cmd);
	}
	else if (tmp && is_binary(tmp->val, all))
	{
		cmd->type = BINARY;
		cmd->status = 0;
		cmd->flag_redirect = false;
		cmd->path_command = path_com(all, tmp->val);
		if (!cmd->path_command)
			return (error_return_int());
		dir_parse(cmd);
		free_path(all);
	}
	return (0);
}

int	is_wtf(t_all *all, t_list *tmp)
{
	struct stat	buf;
	int			res;

	if (tmp->flag == WTF)
	{
		if (is_buildin(tmp->val) || is_binary(tmp->val, all))
		{
			stat(tmp->val, &buf);
			if (!(S_ISDIR(buf.st_mode)))
				tmp->flag = COMMAND;
		}
		if (tmp->flag == WTF)
			res = 1;
		else
			res = 0;
		return (res);
	}
	return (0);
}
