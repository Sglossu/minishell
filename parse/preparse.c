/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/14 18:38:46 by bshawn           ###   ########.fr       */
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

	j = *i;

	while (input[j++])
		if (input[j] == '\"')
			break;
	s = ft_substr(input, 0 , *i);
	m = ft_substr(input, *i + 1, j - *i - 1);
	if (isDollar(s))
		m = ft_dollar(m, all);
	f = strdup(input + j + 1);
	res = ft_strjoin(ft_strjoin(s,m), f);
	// printf("|%s|<-s\n|%s|<-m\n|%s|<-f\n",s,m,f);
	// printf("|%s|<-RES\n", res);
	*i = -1;
	return(res);
}

char *ft_dollar(char *input, t_all *all)
{
	char *varName;
	t_list *envObj;
	char *res;
	int	i;
	int j;

	(void) all;
	(void) envObj;
	res = NULL;
	i = 0;
	while (input[i] != '$' && input[i])
		i++;
	j = i++;
	while (ft_isalnum(input[j]) && input[j])
		j++;
	varName = ft_substr(input, i, j - i);
	// printf("%s < - input\n %s <- varName\n %d <- i\n %d <- j",input, varName, i, j);
	envObj = ft_lstfind(all->env, varName);
	// printf("|%s| < --- env value\n", envObj->val);
	res = find_after_equals(envObj->val);
	return res;
}