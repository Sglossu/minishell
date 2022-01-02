/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:07:53 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:07:55 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_all *all, t_list *arg)
{
	char	*str;

	remember_pwd(all);
	if (!arg->next || (arg->next && !ft_strcmp(arg->next->val, "~")))
	{
		str = home(&all->env);
		if (!str)
			return (g_status);
	}
	else
	{
		str = ft_strdup(arg->next->val);
		if (!str)
			return (error_return_int());
	}
	if (utils_cd(all, str))
	{
		free(str);
		return (g_status);
	}
	g_status = 0;
	free(str);
	return (g_status);
}
