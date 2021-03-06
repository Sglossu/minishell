/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2022/01/02 14:59:15 by bshawn           ###   ########.fr       */
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
	int		x;

	m = ft_substr(str, i + 1, j - i - 1);
	if (!m)
		return (NULL);
	x = 0;
	if (str[i] == '\"' && is_dollar(m) && ft_strlen(m) > 1)
	{
		while (m[x])
		{
			if (m[x] == '$' && (ft_isalnum(m[x + 1]) || m[x + 1] == '?'))
			{
				m = ft_dollar(m, all, &x);
				if (!m)
					return (NULL);
			}
			x++;
		}
	}
	return (m);
}

static void	free_three_line(char **s, char **m, char **f)
{
	if (*s)
		free(*s);
	if (*m)
		free(*m);
	if (*f)
		free(*f);
}

static char	*ft_quote(char *str, t_all *all, int *i, char sym)
{
	char	*s;
	char	*m;
	char	*f;
	int		j;

	j = *i;
	while (str[++j])
		if (str[j] == sym)
			break ;
	s = ft_substr(str, 0, *i);
	if (s)
		m = quote_main_part(str, all, *i, j);
	if (s && m)
		f = strdup(str + j + 1);
	if (!s || !m || !f)
		return (error_return_null());
	free(str);
	*i = j - 2;
	str = ft_strjoin(s, m);
	if (str)
		str = ft_strjoin_gnl(str, f);
	free_three_line(&s, &m, &f);
	if (!str)
		return (error_return_null());
	return (str);
}

char	*ready_string(t_list *tmp, t_all *all, int *flag, int i)
{
	char	*str;

	str = ft_strdup(tmp->val);
	if (!str)
		return (error_return_null());
	if (str)
	{
		while (str[++i])
		{
			if (str && (str[i] == '\'' || str[i] == '\"'))
			{
				str = ft_quote(str, all, &i, str[i]);
				*flag = 1;
			}
			else if (str && str[i] == '$' && (ft_isalpha(str[i + 1])
					|| str[i + 1] == '?'))
				str = ft_dollar(str, all, &i);
			else if (str && str[i] == '\\')
				str = ft_ecran(str, &i);
			if (!str)
				return (NULL);
		}
	}
	free(tmp->val);
	return (str);
}
