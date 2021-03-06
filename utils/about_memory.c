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

	i = 0;
	if (!buf)
		return ;
	while (buf[i])
	{
		free(buf[i]);
		buf[i] = NULL;
		i++;
	}
	free(buf);
	buf = NULL;
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
		return (argv_not_exist(&argv));
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

void	remember_pwd(t_all *all)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd)
	{
		free(all->oldpwd);
		all->oldpwd = ft_strdup(pwd);
		if (!all->oldpwd)
			return (error_return_nothing());
	}
	free(pwd);
}
