/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:18:19 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/31 18:24:32 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	home_exist(t_list *tmp, t_all *all, char *str, int i)
{
	char	*find_aft_eq;

	tmp = ft_lstfind(all->env, "HOME");
	if (tmp)
	{
		find_aft_eq = find_after_equals(tmp->val);
		if (find_aft_eq)
		{
			all->path[i] = ft_strjoin(find_aft_eq, str);
			if (!all->path[i])
				return (error_return_int());
			free(find_aft_eq);
		}
		free(str);
	}
	else
		all->path[i] = NULL;
	return (0);
}

void	loop_for_while(t_all *all, t_list *tmp)
{
	int		i;
	char	*str;

	i = -1;
	while (all->path[++i])
	{
		if (all->path[i][0] == '~')
		{
			str = ft_strdup(all->path[i] + 1);
			if (!str)
				return (error_return_nothing());
			free(all->path[i]);
			if (home_exist(tmp, all, str, i))
				return ;
		}
	}
}

int	parse_path(t_all *all)
{
	t_list	*tmp;
	char	*str;

	if (all->path)
		free_path(all);
	tmp = ft_lstfind(all->env, "PATH");
	if (!tmp)
	{
		all->path = NULL;
		return (1);
	}
	str = find_after_equals(tmp->val);
	if (!str)
		return (1);
	all->path = ft_split(str, ':');
	free(str);
	if (!all->path)
		return (error_return_int());
	loop_for_while(all, tmp);
	return (0);
}
