/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/14 19:45:55 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_quote(char *input, int *i)
{
	char *s;
	char *m;
	char *f;
	char *res;
	int j;

	j = *i;

	while (input[j++])
		if (input[j] == '\'')
			break;
	s = ft_substr(input, 0 , *i);
	m = ft_substr(input, *i + 1, j - *i - 1);
	f = strdup(input + j + 1);
	res = ft_strjoin(ft_strjoin(s,m), f);
	// printf("|%s|<-s\n|%s|<-m\n|%s|<-f\n",s,m,f);
	// printf("|%s|<-RES\n", res);
	*i = -1;
	return(res);
}


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

char *ft_dubquoute(char *input, int *i, t_all *all)
{
	char *s;
	char *m;
	char *f;
	char *res;
	int j;

	(void) all;
	j = *i;

	while (input[j++])
		if (input[j] == '\"')
			break;
	s = ft_substr(input, 0 , *i);
	m = ft_substr(input, *i + 1, j - *i - 1);
	// if (isDollar(s))
	// 	m = ft_dollar(m, all, i);
	f = strdup(input + j + 1);
	res = ft_strjoin(ft_strjoin(s,m), f);
	*i = -1;
	return(res);
}

// char *ft_dollar(char *input, t_all *all, int *ip)
// {
// 	t_list *envObj;
// 	char *res;
// 	int	i;
// 	int j;

// 	i = 0;
// 	while (input[i] != '$' && input[i])
// 		i++;
// 	j = i++;
// 	while (ft_isalnum(input[j]) && input[j])
// 		j++;
	
// 	envObj = ft_lstfind(all->env, ft_substr(input, i, j - i));
// 	res = find_after_equals(envObj->val);
// 	*ip = -1;
// 	return ft_strjoin(ft_strjoin(ft_substr(input, 0 , i), res), strdup(input + j + 1));
// }