/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/11/25 20:15:54 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse(t_all **all, char *input)
{
    if (!ft_strcmp(input, "cd"))
		(*all)->arg = ft_lstnew("cd");
	else if (!ft_strcmp(input, "echo"))
		(*all)->arg = ft_lstnew("echo");
	else if (!ft_strcmp(input, "pwd"))
		(*all)->arg = ft_lstnew("pwd");
	else if (!ft_strcmp(input, "ls"))
		(*all)->arg = ft_lstnew("ls");
	else
		(*all)->arg = NULL;
	return 0;
}
