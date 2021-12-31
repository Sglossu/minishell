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

void    if_arg_exist(t_all *all, char *str)
{
    t_list    *tmp;
    char    *tmp_str;
    char    *find_b_e;
    int        i;

    find_b_e = find_before_equals(str);
    if (!find_b_e)
    {
		tmp = ft_lstfind(all->env, str);
		if (tmp)
			return ;
        ft_lstadd_back(&all->env, ft_lstnew(ft_strdup(str)));
        return ;
    }
    tmp_str = (char *)malloc(sizeof(char) * ft_strlen(find_b_e));
    if (!tmp_str)
        return (error_return_nothing());
    i = -1;
    while (find_b_e[++i + 1])
        tmp_str[i] = find_b_e[i];
//    find_b_e[i] = '\0';
	tmp_str[i] = '\0';
    tmp = ft_lstfind(all->env, tmp_str);
    if (tmp)
        ft_lstremove(&all->env, tmp);
    ft_lstadd_back(&all->env, ft_lstnew(ft_strdup(str)));
    free(tmp_str);
    free(find_b_e);
}

int    error_in_variable(t_list *arg)
{
    ft_printf(2, "export: `%s': not a valid identifier\n", arg->val);
    g_status = 1;
	return (g_status);
}

int    ft_export(t_all *all, t_list *arg)
{
    char		**buf;
    t_list		*tmp;
    int			count;

    if (arg)
        arg = arg->next;
    tmp = arg;
    while (tmp)
    {
        if (str_is_variable(tmp->val))
            return (error_in_variable(tmp));
		if_arg_exist(all, tmp->val);
        tmp = tmp->next;
    }
	tmp = arg;
    if (!tmp)
    {
        new_copy_env(all);
        count = ft_lstsize(all->exp);
        buf = ft_sort_params(count, all->exp);
        if (!(buf))
            return (error_return_int());
        print_params(buf, count);
		free_buf(buf);
    }
    g_status = 0;
    return (g_status);
}
