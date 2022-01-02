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

static	void	withoit_equals(t_all *all, char *str)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = ft_lstfind(all->env, str);
	if (tmp)
		return ;
	tmp_str = ft_strdup(str);
	if (!tmp_str)
		return (error_return_nothing());
	ft_lstadd_back(&all->env, ft_lstnew(tmp_str));
}

static	char	*concatenation_arg(t_list *tmp_was, char **str, t_all *all)
{
	char	*str_tmp;
	char	*str_aft_eq;

	str_aft_eq = find_after_equals(*str);
	if (!str_aft_eq)
		return (NULL);
	str_tmp = ft_strjoin(tmp_was->val, str_aft_eq);
	free(str_aft_eq);
	if (!str_tmp)
		return (NULL);
	ft_lstremove(&all->env, tmp_was);
	free(*str);
	*str = ft_strdup(str_tmp);
	if (!*str)
	{
		free(str_tmp);
		return (NULL);
	}
	free(str_tmp);
	return (*str);
}

void	if_arg_exist(t_all *all, char *str, t_list *old_tmp)
{
	t_list	*tmp;
	char	*tmp_str;
	char	*find_b_e;
	int		i;

	find_b_e = find_before_equals(str);
	if (!find_b_e)
		return (withoit_equals(all, str));
	tmp_str = (char *)malloc(sizeof(char) * ft_strlen(find_b_e));
	if (!tmp_str)
		return (error_return_nothing());
	i = -1;
	while (find_b_e[++i + 1])
		tmp_str[i] = find_b_e[i];
	tmp_str[i] = '\0';
	tmp = ft_lstfind(all->env, tmp_str);
	if (tmp && !old_tmp->flag_add)
		ft_lstremove(&all->env, tmp);
	else if (tmp && old_tmp->flag_add)
		concatenation_arg(tmp, &str, all);
	ft_lstadd_back(&all->env, ft_lstnew(ft_strdup(str)));
	free(tmp_str);
	free(find_b_e);
}

static	void	flag_add_in_arg(t_list *arg)
{
	t_list	*tmp;

	tmp = arg;
	while (tmp)
	{
		tmp->flag_add = false;
		tmp = tmp->next;
	}
}

int	ft_export(t_all *all, t_list *arg)
{
	char	**buf;
	t_list	*tmp;

	g_status = 0;
	flag_add_in_arg(arg);
	if (arg)
		arg = arg->next;
	tmp = arg;
	if (!tmp)
	{
		new_copy_env(all);
		buf = ft_sort_params(ft_lstsize(all->exp), all->exp);
		if (!(buf))
			return (error_return_int());
		print_params(buf, ft_lstsize(all->exp));
	}
	while (tmp)
	{
		if (str_is_variable(tmp->val, tmp))
			return (g_status);
		if_arg_exist(all, tmp->val, tmp);
		tmp = tmp->next;
	}
	return (g_status);
}
