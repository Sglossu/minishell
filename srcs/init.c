/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 23:05:56 by sglossu           #+#    #+#             */
/*   Updated: 2022/01/04 00:32:27 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_malloc(void)
{
	g_status = 12;
	ft_printf(2, "malloc: %s\n", strerror(12));
	exit (g_status);
}

void	add_if_not_shlvl(char **buf, int i, t_list **tmp)
{
	char	*shlvl;

	shlvl = ft_strdup(buf[i]);
	if (shlvl)
		ft_lstadd_back(tmp, ft_lstnew(shlvl));
	else
		error_malloc();
}

static	t_list	*init_lst_env_or_exp(char **buf)
{
	t_list	*tmp;
	int		i;
	bool	flag_shlvl;
	char	*shlvl;

	flag_shlvl = false;
	tmp = NULL;
	i = -1;
	while (buf[++i])
	{
		if (!ft_strncmp(buf[i], "SHLVL=", 6))
		{
			shlvl = change_shlvl(buf[i]);
			if (shlvl)
				ft_lstadd_back(&tmp, ft_lstnew(shlvl));
			else
				error_malloc();
			flag_shlvl = true;
		}
		else
			add_if_not_shlvl(buf, i, &tmp);
	}
	if (!flag_shlvl)
		ft_lstadd_back(&tmp, ft_lstnew("SHLVL=1"));
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
	all->path = NULL;
	init_pwd(all);
	all->i = 0;
	ft_signal_main();
}
