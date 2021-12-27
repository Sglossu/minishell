/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/27 14:58:00 by bshawn           ###   ########.fr       */
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

char *ft_dollar(char *input, t_all *all, int *i)
{
	t_list *envObj;
	char *res;
	char *tmp;
	int j;

	j = *i + 1;
	while (input[j] && input[j] != '\'' && input[j] != '\"' && input[j] != '|' && input[j] != '\\')
		j++;
	tmp = ft_substr(input, *i + 1, j - *i);
	envObj = ft_lstfind(all->env, tmp);
	free(tmp);
	if (envObj)
		tmp = find_after_equals(envObj->val);
	else
	{
		return NULL; // error
	}
	res = ft_strjoin(ft_strjoin(ft_substr(input, 0 , *i), tmp), strdup(input + j + 1));
	free(input);
	return res;
}

char *ft_ecran(char *input, t_all *all, int *i)
{
	int	j;
	char *tmp;
	char *res;

	j = *i;


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

static char *ft_quote(char *str, char sym, int *i, t_all *all)
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
		
	f = strdup(str + j + 1);
	*i = j - 2;
	free(str);
	return(ft_strjoin(ft_strjoin(s,m), f));
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
			str = ft_quote(str, str[i], &i, all);
		if (str[i] == '$')
			str = ft_dollar(str, all, &i);
		if (str[i] == '\\')
			str = ft_ecran(str, all, &i);
		i++;
	}
	return (str);
}
