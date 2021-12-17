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

static void	print_params(char **buf, int count)
{
	int		i;
	int		j;

	j = 0;
	while (j < count)
	{
		i = 0;
		write(STDOUT_FILENO, "declare -x ", 11);
		while (buf[j][i] != 0)
		{
			write(1, &buf[j][i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
}


static int	tmp_not_exist(t_list *exp, char ***buf)
{
	int	count;

	count = ft_lstsize(exp);
	*buf = ft_sort_params(count, exp);
	if (!(*buf))
		return (1); // error
	print_params(*buf, count);
	return (0);
}

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

int	ft_export(t_all *all, t_list *arg)
{
	char	**buf;
	t_list	*tmp;

	tmp = all->env;
	if (arg)
		arg = arg->next;
	tmp = arg;
	new_copy_env(all);
	while (arg)
	{
		if (!ft_isalpha(arg->val[0])) // 1 - значит первая это БУКВА
		{
			ft_printf(2, "export: %s: not a valid identifier\n", arg->val);
			g_status = 1;
		}
		if (!ft_lstfind(all->exp, arg->val))
		{
//			ft_lstadd_back(&exp, ft_lstnew(arg->val));
			ft_lstadd_back(&all->env, ft_lstnew(arg->val));
		}
		arg = arg->next;
	}
	if (!tmp)
		return (tmp_not_exist(all->exp, &buf));
	return (0);
}
