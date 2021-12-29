/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:18:19 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:18:26 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_for_while(t_all *all, t_list *tmp)
{
	int		i;
	char	*str;
	char	*find_aft_eq = NULL;

	i = -1;
	while (all->path[++i])
	{
		if (all->path[i][0] == '~')
		{
			str = ft_strdup(all->path[i] + 1);
			if (!str)
				return (error_return_nothing());
			free(all->path[i]);
			tmp = ft_lstfind(all->env, "HOME");
			if (tmp)
			{
				find_aft_eq = find_after_equals(tmp->val);
				if (find_aft_eq)
				{
					all->path[i] = ft_strjoin(find_aft_eq, str);
					free(find_aft_eq);
				}
				free(str);
			}
			else
				all->path[i] = NULL;
		}
	}
}

int	parse_path(t_all *all)
{
	t_list	*tmp;
	char 	*str;

	tmp = ft_lstfind(all->env, "PATH");
	if (!tmp)
	{
		all->path = NULL;
		return (1); // нет PATH
	}
	str = find_after_equals(tmp->val); // no leaks
	if (!str)
		return (1);
	all->path = ft_split(str, ':');
	free(str);
	if (!all->path)
		return (error_return_int());
	loop_for_while(all, tmp); // тут лики блять
	return (0);
}
