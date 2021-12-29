/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/29 15:41:36 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	isDollar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return 1;
		i++;
	}
	return 0;
}

int	isEcran(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			return 1;
		i++;
	}
	return 0;
}

char *ft_dollar(char *input, t_all *all, int *i)
{
	t_list	*envObj;
	char	*res;
	char	*tmp;
	char	*change;
	int		j;

	j = *i + 1;
	while (input[j] && input[j] != '\'' && input[j] != '\"' && input[j] != '|' && input[j] != '\\')
		j++;
	tmp = ft_substr(input, *i + 1, j - *i);
	if (!tmp)
		return (error_return_null());
	if (!ft_strcmp(tmp, "?"))
	{
		change = ft_itoa(g_status);
		if (!change)
			return(error_return_null());
	}
	else
	{
		envObj = ft_lstfind(all->env, tmp);
		free(tmp);
		if (envObj)
			change = find_after_equals(envObj->val);
		else
		{
			change = ft_strdup("");
			if (!change)
				return (error_return_null());
		}
	}
	res = ft_strjoin(ft_strjoin(ft_substr(input, 0 , *i), change), ft_strdup(input + j + 1));
	free(input);
	free(change);
	return res;
}

char *ft_ecran(char *input, int *i)
{
	char *res;
	char *tmp;
	char *tmp2;

	tmp = ft_substr(input, 0, *i);
	tmp2 = ft_substr(input, *i+1, ft_strlen(input) - *i);
	res = ft_strjoin(tmp, tmp2);

	free(tmp);
	free(tmp2);
	free(input);
	return res;
}

int isDir(char *str)
{
	int i;

	i = 0;
	if (ft_strlen(str) > 2)
		return 0;
	while (str[i])
	{
		if (str[i] != '>' && str[i] != '<')
			return 0;
		i++;
	}
	return 1;	
}

static char *ft_quote(char *str, t_all *all, int *i, char sym)
{
	char	*s;
	char	*m;
	char	*f;
	int		x;
	int		j;

	j = *i;
	while (str[j++])
		if (str[j] == sym)
			break;
	s = ft_substr(str, 0, *i);
	m = ft_substr(str, *i + 1, j - *i - 1);
	if (sym == '\"' && isDollar(m))
	{
		x = 0;
		while (m[x])
		{
			if (m[x] == '$')
				m = ft_dollar(m, all, &x);
			x++;
		}
	}
	if (sym =='\"' && isEcran(m))
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
	*i = j - 2;
	free(str);
	str = ft_strjoin(ft_strjoin(s,m), f);
	free(s);
	free(m);
	free(f);
	return(str);
}


char *ready_string(t_list *tmp, t_all *all)
{
	char	*str;
	int		i;

	str = ft_strdup(tmp->val);
	// if (!str)
	free(tmp->val);
	i = 0;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			str = ft_quote(str, all, &i, str[i]);
		if (str[i] == '$')
			str = ft_dollar(str, all, &i);
		if (str[i] == '\\')
			str = ft_ecran(str, &i);
		i++;
	}
	return (str);
}
