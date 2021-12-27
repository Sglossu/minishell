/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:00:50 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/27 13:00:52 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*error_return_null(void)
{
	g_status = errno;
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (NULL);
}

void	error_return_nothing(void)
{
	g_status = errno;
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return ;
}

int	error_return_int(void)
{
	g_status = errno;
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (g_status);
}
