/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 23:05:56 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 23:06:02 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*init_lst_env_or_exp(char **buf)
{
	t_list	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (buf[i])
	{
		ft_lstadd_back(&tmp, ft_lstnew(buf[i]));
		i++;
	}
	return (tmp);
}

void	init(t_all *all, char **envi)
{
	all->env = init_lst_env_or_exp(envi);
	all->exp = init_lst_env_or_exp(envi);
	all->i = 0;
}
