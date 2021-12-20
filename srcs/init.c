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
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(buf[i])));
		i++;
	}
	return (tmp);
}

static	void	init_pwd(t_all *all)
{
	all->pwd = getcwd(NULL, 1024);
	all->oldpwd = getcwd(NULL, 1024);
	if (!all->pwd)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
	}
}

void	init(t_all *all, char **envi)
{
	all->env = init_lst_env_or_exp(envi);
	all->exp = NULL;
	init_pwd(all);
	all->i = 0;
}
