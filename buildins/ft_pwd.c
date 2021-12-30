/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:09:08 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:09:13 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_all *all)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		g_status = 0;
		return (0);
	}
	ft_putendl_fd(all->oldpwd, STDOUT_FILENO);
	g_status = 0;
	return (1);
}
