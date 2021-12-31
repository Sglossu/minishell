/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/30 07:18:54 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_dir(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 2)
		return (0);
	while (str[i])
	{
		if (str[i] != '>' && str[i] != '<')
			return (0);
		i++;
	}
	return (1);
}

int	is_ecran(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

char	*get_name(char *input, int i)
{
	char	*name;
	int		j;

	name = NULL;
	j = i + 1;
	if (input[j] == '?' || ft_isdigit(input[j]))
	{
		j++;
	}
	else
	{
		while (input[j] && ft_isalnum(input[j]))
		{
			j++;
		}
	}
	name = ft_substr(input, i + 1, j - i - 1);
	if (!name)
		return (error_return_null());
	return (name);
}

char	*get_var_from_path(t_all *all, char *name)
{
	t_list	*env_obj;
	char	*res;

	env_obj = ft_lstfind(all->env, name);
	if (env_obj)
		res = find_after_equals(env_obj->val);
	else
	{
		res = ft_strdup("");
		if (!res)
			return (error_return_null());
	}
	return (res);
}

char	*join_parts(char *input, char *change, char *name, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*res;
	int		j;

	j = i + 1;
	j += ft_strlen(name);
	tmp = ft_substr(input, 0, i);
	if (!tmp)
		return (error_return_null());
	tmp2 = ft_strdup(input + j);
	if (!tmp2)
		return (error_return_null());
	tmp = ft_strjoin_gnl(tmp, change);
	if (!tmp)
		return (error_return_null());
	res = ft_strjoin(tmp, tmp2);
	if (!res)
		return (error_return_null());
	free (tmp);
	free (tmp2);
	return (res);
}

int	ft_len(char *name, char *change)
{
	int	res;
	int	len_name;
	int	len_change;

	len_name = (int)ft_strlen(name);
	len_change = (int)ft_strlen(change);
	res = 0;
	if (!ft_strcmp(change, ""))
	{
		res = -1;
		return (res);
	}
	if (len_name > len_change)
	{
		res = len_name - len_change;
	}
	else if (len_change > len_name)
	{
		res = len_change - len_name;
	}
	return (res);
}

char	*ft_dollar(char *input, t_all *all, int *i)
{	
	char	*res;
	char	*name;
	char	*change;
	int		len;

	name = get_name(input, *i);
	if (!ft_strcmp(name, "?"))
	{
		change = ft_itoa(g_status);
		if (!change)
			return (error_return_null());
	}
	else
		change = get_var_from_path(all, name);
	res = join_parts(input, change, name, *i);
	len = ft_len(name, change);
	*i += len;
	if (name)
		free(name);
	if (input)
		free(input);
	if (change)
		free(change);
	return (res);
}

char	*ft_ecran(char *input, int *i)
{
	char	*res;
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(input, 0, *i);
	if (!tmp)
		return (error_return_null());
	tmp2 = ft_substr(input, *i + 1, ft_strlen(input) - *i);
	if (!tmp2)
		return (error_return_null());
	res = ft_strjoin(tmp, tmp2);
	if (!res)
		return (error_return_null());
	free(tmp);
	free(tmp2);
	free(input);
	return (res);
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
	m = ft_substr(str, *i + 1, j - *i - 1);
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
	f = strdup(str + j + 1);
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
				*flag = 1;
			}
			if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '?'))
				str = ft_dollar(str, all, &i);
			if (str[i] == '\\')
				str = ft_ecran(str, &i);
			i++;
		}
	}
	free(tmp->val);
	return (str);
}
