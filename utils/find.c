/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:16:50 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:16:58 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *find_after_equals(char *str)
{
	bool	equals;

	equals = false;
	if (!str)
		return (NULL); // в cd этот вариант обрабатывается раньше, от туда сюда точно не зайдет, но оставлю на будущее на всякий
	else
	{
		while (*str)
		{
			if (*str == '=')
			{
				equals = true;
				str++;
				break;
			}
			str++;
		}
	}
	if (equals)
		return (ft_strdup(str));
	return (NULL);
}

