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

static	void	loop_for_while(t_all *all, t_list *tmp)
{
	int		i;
	char	*str;

	i = 0;
	while (all->path[i])
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
		i++;
	}
}

int	parse_path(t_all *all)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = ft_lstfind(all->env, "PATH");
	if (!tmp)
	{
		all->path = NULL;
		return (1); // нет PATH
	}
	all->path = ft_split(find_after_equals(tmp->val), ':');
	if (!all->path)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_status = errno;
		return (g_status); // проблема с маллок
	}
	loop_for_while(all, tmp);
	return (0);
}
