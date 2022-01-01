/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/31 18:59:45 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_ecran(char *input, int *i)
{
	char	*res;
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(input, 0, *i);
	if (!tmp)
	{
		g_status = errno;
		return (NULL);
	}
	tmp2 = ft_substr(input, *i + 1, ft_strlen(input) - *i);
	if (!tmp2)
	{
		g_status = errno;
		return (NULL);
	}
	res = ft_strjoin(tmp, tmp2);
	if (!res)
		return (error_return_null());
	free(tmp);
	free(tmp2);
	free(input);
	return (res);
}

static char	*quote_main_part(char *str, t_all *all, int i, int j)
{
	char	*m;
	char	sym;
	int		x;

	sym = str[i];
	m = ft_substr(str, i + 1, j - i - 1);
	x = 0;
	if (sym == '\"' && is_dollar(m) && ft_strlen(m) > 1)
	{
		while (m[x])
		{
			if (m[x] == '$' && (ft_isalnum(m[x + 1]) || m[x + 1] == '?'))
				m = ft_dollar(m, all, &x);
			x++;
		}
	}
	if (sym == '\"' && is_ecran(m))
	{
		x = 0;
		while (m[x])
		{
			if (m[x] == '\\')
				m = ft_ecran(m, &x);
			x++;
		}
	}
	return (m);
}

static char	*ft_quote(char *str, t_all *all, int *i, char sym)
{
	char	*s;
	char	*m;
	char	*f;
	int		x;
	int		j;

	j = *i;
	x = 0;
	while (str[j++])
		if (str[j] == sym)
			break ;
	s = ft_substr(str, 0, *i);
	if (!s)
		return (error_return_null());
	m = quote_main_part(str, all, *i, j);
	if (!m)
		return (error_return_null());
	f = strdup(str + j + 1);
	if (!f)
		return (error_return_null());
	if (x == 0)
		*i = j - 1;
	free(str);
	str = ft_strjoin(ft_strjoin(s, m), f);
	free(s);
	free(m);
	free(f);
	return (str);
}

char	*ready_string(t_list *tmp, t_all *all, int *flag)
{
	char	*str;
	int		i;

	str = ft_strdup(tmp->val);
	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				str = ft_quote(str, all, &i, str[i]);
				if (!str)
					return (NULL);
				*flag = 1;
			}
			if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '?'))
			{
				str = ft_dollar(str, all, &i);
				if (!str)
					return (NULL);
			}
			if (str[i] == '\\')
			{
				str = ft_ecran(str, &i);
				if (!str)
					return (error_return_null());
			}
			i++;
		}
	}
	free(tmp->val);
	return (str);
}
