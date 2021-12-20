/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:12:54 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/09 20:08:00 by bshawn           ###   ########.fr       */
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
	// *i = -1;
	if (input)
	{
		free(input);
		input = NULL;
	}
	return(res);
}

// char *ft_dubquoute(char *input, int *i)
// {

// }

// char *ft_dollar(char *input, int *i)
// {

// }