/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 19:09:07 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/26 19:09:09 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *str_arg_in_quote(char *str)
{
    char    *str1;
    char    *str2;
    char    *tmp;

    tmp = find_before_equals(str);
    if (!tmp)
        return (ft_strdup(str));
    str1 = ft_strjoin(tmp, "\"");
    free(tmp);
    tmp = NULL;
    tmp = find_after_equals(str);
    str2 = ft_strjoin(tmp, "\"");
    free(tmp);
    tmp = NULL;
    tmp = ft_strjoin(str1, str2);
    if (!tmp)
    {
        g_status = errno;
        ft_putendl_fd(strerror(errno), STDERR_FILENO);
    }
    free(str1);
    free(str2);
    str1 = NULL;
    str2 = NULL;
    return (tmp);
}

void    new_copy_env(t_all *all)
{
    t_list	*tmp;
    char	*tmp_str;

    if (all->exp)
        ft_lstclear(&all->exp, free);
    all->exp = NULL;
    tmp = all->env;
    while (tmp)
    {
        tmp_str = str_arg_in_quote(tmp->val);
        ft_lstadd_back(&all->exp, ft_lstnew(ft_strdup(tmp_str))); // защитить strdup
        free(tmp_str);
        tmp_str = NULL;
        tmp = tmp->next;
    }
}
