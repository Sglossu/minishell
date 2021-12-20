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

char *ft_quote(t_str *myString, char sym)
{
	char *s;
	char *m;
	char *f;
	char *res;
	int j;

	j = myString->iter;

	while (myString->input[j++])
		if (myString->input[j] == sym)
			break;
	s = ft_substr(myString->input, 0, myString->iter);
	m = ft_substr(myString->input, myString->iter + 1, j - myString->iter - 1);
	f = strdup(myString->input + j + 1);
	res = ft_strjoin(ft_strjoin(s,m), f);
	myString->iter = j - 2;
	// printf("|%s|<-s\n|%s|<-m\n|%s|<-f\n",s,m,f);
	// printf("|%s|<-RES\n", res);
	return(res);
}
