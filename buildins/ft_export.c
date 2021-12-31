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

void	if_arg_exist(t_all *all, char *str)
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
	if (tmp)
		ft_lstremove(&all->env, tmp);
	ft_lstadd_back(&all->env, ft_lstnew(ft_strdup(str)));
	free(tmp_str);
	free(find_b_e);
}

int	ft_export(t_all *all, t_list *arg)
{
	char	**buf;
	t_list	*tmp;
	int		count;

	g_status = 0;
	if (arg)
		arg = arg->next;
	tmp = arg;
	if (!tmp)
	{
		new_copy_env(all);
		count = ft_lstsize(all->exp);
		buf = ft_sort_params(count, all->exp);
		if (!(buf))
			return (error_return_int());
		print_params(buf, count);
	}
	while (tmp)
	{
		if (str_is_variable(tmp->val))
			return (g_status);
		if_arg_exist(all, tmp->val);
		tmp = tmp->next;
	}
	return (g_status);
}
