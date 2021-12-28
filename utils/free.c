/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:17:03 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:17:05 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_free(t_all *all)
{
	int	i;

	i = 0;
	while (all->cmd[i])
	{
		free(all->cmd[i]);
		i++;
	}
	free(all->cmd);
	all->cmd = NULL;
	all->number_command = 0;
	all->i = 0;
	return (0);
}
