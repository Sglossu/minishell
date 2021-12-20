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

static	void	if_arg_exist(t_all *all, char *str)
{
	t_list	*tmp;
	char 	*tmp_str;
	char	*find_b_e;
	int 	i;

	i = 0;
	find_b_e = find_before_equals(str);
	if (!find_b_e)
	{
		ft_lstadd_back(&all->env, ft_lstnew(str));
		return ;
	}
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
	find_b_e[i] = '\0';
	tmp = ft_lstfind(all->env, tmp_str);
	if (tmp)
		ft_lstremove(&all->env, tmp);
	ft_lstadd_back(&all->env, ft_lstnew(str));
	free(tmp_str);
	free(find_b_e);
}

int	ft_export(t_all *all, t_list *arg)
{
	char	**buf;
	t_list	*tmp;
	int 	count;

	if (arg)
		arg = arg->next;
	tmp = arg;
	while (arg)
	{
		if (str_is_variable(arg->val))
		{
			ft_printf(2, "export: %s: not a valid identifier\n", arg->val);
			g_status = 1;
		}
		else if (!ft_lstfind(all->env, arg->val))
		{
			if_arg_exist(all, arg->val);
		}
		arg = arg->next;
	}
	if (!tmp)
	{
		new_copy_env(all);
		count = ft_lstsize(all->exp);
		buf = ft_sort_params(count, all->exp);
		if (!(buf))
			return (1); // error
		print_params(buf, count);
	}
	return (0);
}
