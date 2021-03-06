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

char	*str_arg_in_quote(char *str)
{
	char	*str1;
	char	*str2;
	char	*tmp;

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

void	new_copy_env(t_all *all)
{
	t_list	*tmp;
	char	*tmp_str;
	char	*tmp_strdp;

	if (all->exp)
		ft_lstclear(&all->exp, free);
	all->exp = NULL;
	tmp = all->env;
	while (tmp)
	{
		tmp_str = str_arg_in_quote(tmp->val);
		if (!tmp_str)
			return ;
		tmp_strdp = ft_strdup(tmp_str);
		if (!tmp_strdp)
			return (error_return_nothing());
		ft_lstadd_back(&all->exp, ft_lstnew(tmp_strdp));
		free(tmp_str);
		tmp_str = NULL;
		tmp = tmp->next;
	}
}

char	*str_without_one_plus(char *str, t_list *tmp)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(sizeof(char) * ft_strlen(str));
	if (!dst)
		return (error_return_null());
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=' )
		{
			tmp->flag_add = true;
			break ;
		}
		dst[i] = str[i];
		i++;
	}
	while (str[i])
	{
		dst[i] = str[i + 1];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	error_in_variable(char *str)
{
	ft_printf(2, "export: `%s': not a valid identifier\n", str);
	g_status = 1;
	return (g_status);
}

int	str_is_variable(char *str, t_list *tmp)
{
	int		i;
	char	*tmp_str;

	tmp_str = str_without_one_plus(str, tmp);
	if (!tmp_str && !g_status)
		return (g_status);
	i = 0;
	if (g_status || (!ft_isalpha(tmp_str[i]) && tmp_str[i] != '_'))
		return (error_in_variable(str));
	i++;
	while (tmp_str[i] && tmp_str[i] != '=')
	{
		if (!ft_isalnum(tmp_str[i]) && tmp_str[i] != '_')
		{
			free(tmp_str);
			return (error_in_variable(str));
		}
		i++;
	}
	free(str);
	str = ft_strdup(tmp_str);
	if (!str)
		return (error_return_int());
	free(tmp_str);
	return (0);
}
