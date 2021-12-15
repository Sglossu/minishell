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

char	*home(t_list **env)
{
	t_list	*tmp;
	char 	*str;

	tmp = ft_lstfind((*env), "HOME");
	if (!tmp)
	{
		ft_putendl_fd("cd: HOME not set", STDOUT_FILENO);
		s_status = 1;
	}
	else
	{
		str = find_after_equals(tmp->val);
		if (!str) // нет =
		{
			ft_putendl_fd("cd: HOME not set", STDOUT_FILENO);
			s_status = 1;
		}
		else
			return (str);
	}
	return (NULL);
}

void	change_pwd_oldpwd(t_list **env, char **oldpwd)
{
	char	*pwd;
	t_list	*tmp;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
	{
		s_status = errno;
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
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("OLDPWD=", *oldpwd)));
	else
		tmp->val = ft_strjoin("OLDPWD=", *oldpwd);
}

int	ft_cd(t_list **env, t_list *arg)
{
	(void)env;
	char 	*str;
	char 	*oldpwd;

	if (!arg->next)
		str = home(env);
	else
		str = ft_strdup(arg->next->val);
	if (!str)
		return (s_status); // error - уже напечатана
	oldpwd = getcwd(NULL, 1024);
	if (!oldpwd)
	{
		s_status = errno;
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (s_status);
	}
	if (chdir(str) == -1 && str)
	{
		s_status = errno;
		ft_putendl_fd("cd: ", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
		ft_putchar_fd(' ', STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
		change_pwd_oldpwd(env, &oldpwd);
	return (s_status);
}
