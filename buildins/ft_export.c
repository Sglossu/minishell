/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:09:29 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:10:12 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_copy_env(t_all *all)
{
	t_list	*tmp;

	ft_lstclear(&all->exp, free);

	all->exp = NULL;
	tmp = all->env;
	if (tmp)
		ft_lstadd_back(&all->exp, ft_lstnew(tmp->val));
	else
		return ;
	if (tmp)
		tmp = tmp->next;
	else
		return ;
	while (tmp)
	{
		ft_lstadd_back(&all->exp, ft_lstnew(tmp->val));
		tmp = tmp->next;
	}
}

static int	tmp_not_exist(t_all *all, char ***buf)
{
	int	count;

	new_copy_env(all);
	count = ft_lstsize(all->exp);
	*buf = ft_sort_params(count, all->exp);
	if (!(*buf))
		return (1); // error
	print_params(*buf, count);
	return (0);
}

static	char	*str_arg(char *str)
{
	char	*str1;
	char 	*str2;
	char 	*tmp;

	tmp = find_before_equals(str);
	if (!tmp)
		return (ft_strdup(str));
	str1 = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp = find_after_equals(str);
	str2 = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (tmp);
}

static	void	if_arg_exist(t_all *all, char *str)
{
	t_list	*tmp;
	char 	*tmp_str;
	char	*find_b_e;
	int 	i;

	i = 0;
	find_b_e = find_before_equals(str);
	tmp_str = (char *)malloc(sizeof(char) * ft_strlen(find_b_e));
	if (!tmp_str)
	{
//		error
		return ;
	}
	while (find_b_e[i + 1])
	{
		tmp_str[i] = find_b_e[i];
		i++;
	}
	tmp = ft_lstfind(all->env, tmp_str);
	if (!tmp)
	{
		ft_lstadd_back(&all->env, ft_lstnew(str));
	}
	else
	{
		change_after_equals_in_list(all, *tmp, str);
	}
	free(tmp_str);
	free(find_b_e);
}

int	ft_export(t_all *all, t_list *arg)
{
	char	**buf;
	t_list	*tmp;
	char 	*arg_str;

	tmp = all->env;
	if (arg)
		arg = arg->next;
	tmp = arg;
//	new_copy_env(all);
	while (arg)
	{
		if (!ft_isalpha(arg->val[0])) // 1 - значит первая это БУКВА
		{
			ft_printf(2, "export: %s: not a valid identifier\n", arg->val);
			g_status = 1;
		}
		if (!ft_lstfind(all->exp, arg->val))
		{
			arg_str = str_arg(arg->val); // делает нормальную строчку для добавления в список
			if_arg_exist(all, arg_str);
		}
		arg = arg->next;
	}
	if (!tmp)
		return (tmp_not_exist(all, &buf));
	return (0);
}
