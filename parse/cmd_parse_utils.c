/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:21:55 by bshawn            #+#    #+#             */
/*   Updated: 2022/01/01 18:10:44 by bshawn           ###   ########.fr       */
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
