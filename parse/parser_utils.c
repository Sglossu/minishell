/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:15:53 by sglossu           #+#    #+#             */
/*   Updated: 2022/01/03 14:22:31 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	path_pl_command(t_all *all, char *command)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	while (all->path && all->path[i])
	{
		str1 = ft_strdup(all->path[i]);
		free(all->path[i]);
		str2 = ft_strjoin("/", command);
		all->path[i] = ft_strjoin(str1, str2);
		free(str2);
		free(str1);
		i++;
	}
}

int	find_com(t_all *all, char *command)
{
	int	i;
	int	x;
	int	flag;

	i = 0;
	flag = 1;
	while (all->path && all->path[i])
	{
		x = 0;
		while (all->path[i][x++])
			if (all->path[i][x] && all->path[i][x] == '/' && all->path[i][x + 1] == '/')
				flag = 0;
		if (!access(all->path[i], 1) && flag)
		{
			return (1);
		}
		i++;
		flag = 1;
	}
	if (!access(command, 1))
	{
		return (1);
	}
	return (0);
}

char	*path_com(t_all *all, char *command)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (all->path && all->path[i])
	{
		if (!access(all->path[i], 0 | 1))
		{
			str = ft_strdup(all->path[i]);
			if (!str)
				return (error_return_null());
			return (str);
		}
		i++;
	}
	if (!access(command, 0 | 1))
	{
		str = ft_strdup(command);
		if (!str)
			return (error_return_null());
		return (str);
	}
	return (NULL);
}

int	is_binary(char *val, t_all *all)
{
	int	res;

	free_path(all);
	parse_path(all);
	path_pl_command(all, val);
	res = find_com(all, val);
	return (res);
}

int	is_buildin(char *val)
{
	if ((!ft_strcmp(val, "cd")) || (!ft_strcmp(val, "pwd"))
		|| (!ft_strcmp(val, "echo"))
		|| (!ft_strcmp(val, "export")) || (!ft_strcmp(val, "unset"))
		|| (!ft_strcmp(val, "env")) || (!ft_strcmp(val, "exit")))
		return (1);
	else
		return (0);
}
