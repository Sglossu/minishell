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

//
// Created by Shasta Glossu on 11/16/21.
//

#include "../includes/minishell.h"

static char	*home(t_list **env)
{
	t_list	*tmp;
	char	*str;

	tmp = ft_lstfind((*env), "HOME");
	if (!tmp)
	{
		ft_putendl_fd("cd: HOME not set", STDOUT_FILENO);
		g_status = 1;
	}
	else
	{
		str = find_after_equals(tmp->val);
		if (!str) // нет =
		{
			ft_putendl_fd("cd: HOME not set", STDOUT_FILENO);
			g_status = 1;
		}
		else
			return (str);
	}
	return (NULL);
}

static void	change_pwd_oldpwd(t_list **env, t_list *exp, char **oldpwd)
{
	char	*pwd;
	t_list	*tmp;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
	{
		g_status = errno;
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	tmp = ft_lstfind(*env, "PWD");
	if (!tmp)
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("PWD=", pwd)));
	else
		tmp->val = ft_strjoin("PWD=", pwd);
	tmp = ft_lstfind(*env, "OLDPWD");
	if (!tmp)
	{
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("OLDPWD=", *oldpwd)));
		ft_lstadd_back(&exp, ft_lstnew(ft_strjoin("OLDPWD=", *oldpwd)));
	}
	else
		tmp->val = ft_strjoin("OLDPWD=", *oldpwd);
}

void	remember_pwd(t_all *all)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd)
	{
		free(all->pwd);
		all->pwd = ft_strdup(pwd);
	}
	free(pwd);
}

int	ft_cd(t_all *all, t_list **env, t_list *exp, t_list *arg)
{
	char	*str;
	char	*oldpwd;

	remember_pwd(all);
	if (!arg->next)
		str = home(env);
	else
		str = ft_strdup(arg->next->val);
	if (!str)
		return (g_status); // error - уже напечатана
	oldpwd = getcwd(NULL, 1024);
	if (!oldpwd)
	{
		g_status = errno;
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (g_status);
	}
	if (chdir(str) == -1 && str)
	{
		g_status = errno;
		ft_printf(2, "cd: %s: %s\n", str, strerror(errno));
	}
	else
		change_pwd_oldpwd(env, exp, &oldpwd);
	return (g_status);
}
