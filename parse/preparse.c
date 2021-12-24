/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/16 21:35:59 by bshawn           ###   ########.fr       */
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
	int j;

	j = *i + 1;
	while (input[j] && input[j] != '\'' && input[j] != '\"' && input[j] != '|')
		j++;
	
	res = ft_substr(input, *i + 1, j - *i);
	printf("|%s|\n", res);
	envObj = ft_lstfind(all->env, res);
	if (envObj)
		res = find_after_equals(envObj->val);
	return ft_strjoin(ft_strjoin(ft_substr(input, 0 , *i), res), strdup(input + j + 1));
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

static char *ft_quote(char *str, char sym, int *i)
{
	char *s;
	char *m;
	char *f;
	char *res;
	int j;

	j = *i;

	while (str[j++])
		if (str[j] == sym)
			break;
	s = ft_substr(str, 0, *i);
	m = ft_substr(str, *i + 1, j - *i - 1);
	f = strdup(str + j + 1);
	res = ft_strjoin(ft_strjoin(s,m), f);
	*i = j - 2;
	// printf("|%s|<-s\n|%s|<-m\n|%s|<-f\n",s,m,f);
	// printf("|%s|<-RES\n", res);
	free(str);
	return(res);
}

char *ready_string(t_list *tmp, t_all *all)
{
	char	*str;
	int		i;

	str = ft_strdup(tmp->val);
	free(tmp->val);
	i = 0;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			str = ft_quote(str, str[i], &i);
		if (str[i] == '$')
			str = ft_dollar(str, all, &i);
		i++;
	}
	return (str);
}
