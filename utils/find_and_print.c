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

char	*find_after_equals(char *str)
{
	bool	equals;
	int 	i;

	i = 0;
	equals = false;
	if (!str)
		return (NULL); // в cd этот вариант обрабатывается раньше, от туда сюда точно не зайдет, но оставлю на будущее на всякий
	while (str[i])
	{
		if (str[i] == '=')
		{
			equals = true;
			i++;
			break ;
		}
		i++;
	}
	if (equals)
		return (ft_substr(str, i, ft_strlen(str) - i));
	return (NULL);
}

char	*find_before_equals(char *str)
{
	int		i;
	char	*dst;
	int 	j;

	i = 0;
	j = 0;
	if (!ft_strchr(str, '='))
		return NULL;
	while (str[i])
	{
		if (str[i] == '=')
			break;
		i++;
	}
	i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
	{
//		error// todo
		return NULL;
	}
	while (i > 0)
	{
		dst[j] = str[j];
		j++;
		i--;
	}
	dst[j] = '\0';
	return (dst);
}

int	str_is_variable(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_') // 0 - нет буквы
		return (1);
	i++;
	while(str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	print_params(char **buf, int count)
{
	int		i;
	int		j;

	j = 0;
	while (j < count)
	{
		i = 0;
		write(STDOUT_FILENO, "declare -x ", 11);
		while (buf[j][i] != 0)
		{
			write(1, &buf[j][i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
}
