/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:16:50 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/31 17:32:12 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_after_equals(char *str)
{
	bool	equals;
	int		i;
	char	*str_find;

	i = 0;
	equals = false;
	if (!str)
		return (NULL);
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
	{
		str_find = ft_substr(str, i, ft_strlen(str) - i);
		if (!str_find)
			return (error_return_null());
		return (str_find);
	}
	return (NULL);
}

char	*find_before_equals(char *str)
{
	int		i;
	char	*dst;
	int		j;

	i = -1;
	j = 0;
	if (!ft_strchr(str, '='))
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (error_return_null());
	while (i > 0)
	{
		dst[j] = str[j];
		j++;
		i--;
	}
	dst[j] = '\0';
	return (dst);
}

void	print_params(char **buf, int count)
{
	int		j;

	j = 0;
	while (j < count)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		ft_putendl_fd(buf[j], STDOUT_FILENO);
		j++;
	}
}

void	print_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_putendl_fd(tmp->val, STDERR_FILENO);
		tmp = tmp->next;
	}
}
