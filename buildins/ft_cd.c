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

static char	*home(t_list **env)
{
	t_list	*tmp;
	char	*str;

	tmp = ft_lstfind((*env), "HOME");
	if (!tmp)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		g_status = 1;
	}
	else
	{
		str = find_after_equals(tmp->val);
		if (!str)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			g_status = 1;
		}
		else
			return (str);
	}
	return (NULL);
}

static void	change_pwd_oldpwd(t_all *all, t_list **env, char **oldpwd)
{
	char	*pwd;
	t_list	*tmp;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
		return (error_return_nothing());
	tmp = ft_lstfind(*env, "PWD");
	if (!tmp)
		all->pwd = ft_strdup(pwd);
	else
		tmp->val = ft_strjoin("PWD=", pwd);
	tmp = ft_lstfind(*env, "OLDPWD");
	if (!tmp)
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("OLDPWD=", *oldpwd)));
	else
		tmp->val = ft_strjoin("OLDPWD=", *oldpwd);
}

static	int	utils_cd(t_all *all, char *str)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 1024);
	if (!oldpwd)
	{
		oldpwd = ft_strdup(all->oldpwd);
		if (!oldpwd)
			return (error_return_int());
	}
	if (str && chdir(str) == -1)
	{
		chdir(all->oldpwd);
		if (str && chdir(str) == -1)
		{
			g_status = errno;
			ft_printf(2, "cd: %s: %s\n", str, strerror(errno));
			return (g_status);
		}
	}
	else
		change_pwd_oldpwd(all, &all->env, &oldpwd);
	return (0);
}

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
		return (g_status);
	g_status = 0;
	return (g_status);
}
