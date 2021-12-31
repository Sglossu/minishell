/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:11:30 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/27 20:11:43 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	shlvl_classic_number(int shlvl, char **str_new)
{
	char	*nb_str;

	nb_str = ft_itoa(shlvl + 1);
	if (!nb_str)
		return (error_return_nothing());
	else
	{
		*str_new = ft_strjoin("SHLVL=", nb_str);
		free(nb_str);
	}
}

char	*change_shlvl(char *str_old)
{
	char	*str_new;
	int		shlvl;

	shlvl = ft_atoi(str_old + 6);
	if (!ft_isdigit(str_old[6]) && str_old[6] != '-')
		str_new = ft_strdup("SHLVL=1");
	else if (shlvl == 0)
		str_new = ft_strdup("SHLVL=1");
	else if (shlvl < 0)
		str_new = ft_strdup("SHLVL=0");
	else if (shlvl >= 999)
		str_new = ft_strdup("SHLVL=");
	else
	{
		shlvl_classic_number(shlvl, &str_new);
	}
	if (!str_new)
		return (NULL);
	return (str_new);
}
