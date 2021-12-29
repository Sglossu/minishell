/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:15:53 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:15:55 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	path_pl_command(t_all *all, char *command)
{
	int 	i = 0;
	char 	*str1;
	char 	*str2;

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

int  find_com(t_all *all, char *command)
{
	int i = 0;

	while (all->path && all->path[i])
	{
		if (!access(all->path[i], 0 | 1))
		{
			return (1);
		}
		i++;
	}
	if (!access(command, 0 | 1))
	{
		// printf("|%s|\n", command);
		return (1);
	}
	return (0);
}

char *path_com(t_all *all, char *command)
{
	int i = 0;
	char	*str = NULL;
//	parse_path(all); зачем второй раз?
//	path_pl_command(all, command);

	while (all->path && all->path[i])
	{
		if (!access(all->path[i], 0 | 1))
		{
			// printf("|%s|\n", all->path[i]);
			str = ft_strdup(all->path[i]);
			if (!str)
				return (error_return_null());
			return (str);
		}
		i++;
	}
	if (!access(command, 0 | 1))
	{
		// printf("|%s|\n", command);
		str = ft_strdup(command);
		if (!str)
			return (error_return_null());
		return (str);
	}
	return (NULL);
}

int is_binary(char *val, t_all *all)
{
	free_path(all); // это оставить
	parse_path(all);
	path_pl_command(all, val);
	return(find_com(all, val));
}

int is_buildin(char *val)
{
	if ((!ft_strcmp(val, "cd")) || (!ft_strcmp(val, "pwd")) || (!ft_strcmp(val, "echo"))
			|| (!ft_strcmp(val, "export")) || (!ft_strcmp(val, "unset"))
				|| (!ft_strcmp(val, "env")) || (!ft_strcmp(val, "exit")))
		return 1;
	else
		return 0;
}

