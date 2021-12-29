/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:18:19 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/29 14:14:18 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			free(all->path[i]);
			tmp = ft_lstfind(all->env, "HOME");
			if (tmp)
			{
				all->path[i] = ft_strjoin(find_after_equals(tmp->val), str);
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
	int		i;

	i = -1;
	if (all->path)
	{
		while (all->path[++i])
			free(all->path[i]);
		all->path = NULL;
	}
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
	loop_for_while(all, tmp);
	return (0);
}
