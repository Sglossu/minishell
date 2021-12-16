/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:16:27 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:16:35 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*split_for_dup(char *str, char c)
{
	while (*str != c)
		str++;
	str++;
	return (ft_strdup(str));
}

void	free_buf(char **buf)
{
	int	i;
	int	j;

	i = 0;
	while (buf[i])
	{
		j = 0;
		while (buf[j])
		{
			free(buf[j]);
			buf[j] = NULL;
			j++;
		}
		free(buf[i]);
		buf[i] = NULL;
		i++;
	}
}

static	char	**argv_not_exist(char ***argv)
{
	free_buf(*argv);
	g_status = errno;
	return (NULL);
}

char	**from_lst_to_buf(int argc, t_list *lst, char c)
{
	char	**argv;
	int		i;

	i = 0;
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!argv)
	{
		g_status = errno;
		return (NULL);
	}
	argv[argc] = NULL;
	while (lst)
	{
		if (c == '=')
			argv[i] = split_for_dup(lst->val, c);
		else
			argv[i] = ft_strdup(lst->val);
		if (!argv[i])
			return (argv_not_exist(&argv));
		i++;
		lst = lst->next;
	}
	return (argv);
}
