/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 23:05:56 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 23:06:02 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp2(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (((unsigned char)str1[i] != '\0' && (unsigned char)str2[i] != '\0') \
	&& i < n)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (((unsigned char)str1[i] != '\0' || (unsigned char)str2[i] != '\0') \
	&& i < n)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}

static	t_list	*init_lst_env_or_exp(char **buf)
{
	t_list	*tmp;
	int		i;
	// bool	flag_shlvl;
	char	*shlvl;

	// flag_shlvl = false;
	tmp = NULL;
	i = 0;
	while (buf[i])
	{
		if (!ft_strncmp(buf[i], "SHLVL=", 6))
		{
//			write(1, "________________________________________\n", 41);
			shlvl = change_shlvl(buf[i]);
			ft_lstadd_back(&tmp, ft_lstnew("SHLVL=1"));
			// flag_shlvl = true;
		}
		else
		{
			shlvl = ft_strdup(buf[i]);
			ft_lstadd_back(&tmp, ft_lstnew(shlvl));
		}
		i++;
	}
	// if (!flag_shlvl)
	// 	ft_lstadd_back(&tmp, ft_lstnew("SHLVL=1"));
	return (tmp);
}

static	void	init_pwd(t_all *all)
{
	all->pwd = getcwd(NULL, 1024);
	all->oldpwd = getcwd(NULL, 1024);
	if (!all->pwd)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
	}
}

void	init(t_all *all, char **envi)
{
	all->env = init_lst_env_or_exp(envi);
	all->exp = NULL;
	init_pwd(all);
	all->i = 0;
}
