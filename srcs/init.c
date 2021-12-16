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

static	t_list	*init_lst_env_or_exp(char **buf)
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

//int	init_pwd(t_all *all)
//{
//
//}

void	init(t_all *all, char **envi)
{
//	t_list	*tmp;
	all->env = init_lst_env_or_exp(envi);
	all->exp = init_lst_env_or_exp(envi);
//	tmp = ft_lstfind(all->exp, "PWD");
//	if (tmp)
//		all->pwd = ft_strdup(tmp->val);
//	else
//		all->pwd = NULL;
	all->i = 0;
}
