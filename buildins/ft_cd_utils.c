/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alexandra <Alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:36:22 by Alexandra         #+#    #+#             */
/*   Updated: 2022/01/02 21:37:47 by Alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*home(t_list **env)
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
	{
		free(tmp->val);
		tmp->val = ft_strjoin("PWD=", pwd);
	}
	tmp = ft_lstfind(*env, "OLDPWD");
	if (!tmp)
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("OLDPWD=", *oldpwd)));
	else
	{
		free(tmp->val);
		tmp->val = ft_strjoin("OLDPWD=", *oldpwd);
	}
	free(pwd);
}

int	try_name_with_space(t_all *all, char *str, char **oldpwd)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = all->cmd[all->i]->arg->next->next;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp_str = ft_strjoin_gnl(str, " ");
		if (!tmp_str)
			return (error_return_int());
		str = ft_strjoin_gnl(tmp_str, tmp->val);
		if (!str)
			return (error_return_int());
		if (chdir(str))
		{
			change_pwd_oldpwd(all, &all->env, oldpwd);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static	int	error_cd(char *str, char *oldpwd)
{
	g_status = errno;
	ft_printf(2, "cd: %s: %s\n", str, strerror(errno));
	free(oldpwd);
	return (g_status);
}

int	utils_cd(t_all *all, char *str)
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
		if (try_name_with_space(all, str, &oldpwd))
		{
			free(oldpwd);
			return (g_status);
		}
		chdir(all->oldpwd);
		if (str && chdir(str) == -1)
			return (error_cd(str, oldpwd));
	}
	else
		change_pwd_oldpwd(all, &all->env, &oldpwd);
	free(oldpwd);
	return (0);
}
