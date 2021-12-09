/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/09 13:20:16 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  (мои друзья)    ''  ""  \   $  |  > < >> <<  (мои друзья)

int	parse(t_all *all, char *input)
{
	t_list		*HEAD;

	parse_path(all);			
	HEAD = make_list_with_all_word(input);
	all->number_command = num_of_commands(HEAD, all);
	init_cmd_struct(all);
	fill_cmd_struct(all, HEAD);

	return 0;
}

// static char *ft_quote(char *str, int *i)
// {
// 	char	*before;
// 	char	*main;
// 	char	*after;
// 	int		j;

// 	j = *i;							// Старт (указатель на ковычку)
// 	while (str[(*i)++])
// 		if (str[*i] == '\'')        // Конец (узнали, где ковычка закрывается)
// 			break;

// 	// printf("%d <-j   %d <- i\n", j, *i);
// 	before = ft_substr(str, 0, j);
// 	// printf("|%s| < -- I \n", before);
// 	main = ft_substr(str, j + 1, *i - j - 1);
// 	// printf("|%s| < -- II \n", main);
// 	after = ft_strdup(str + *i + 1);
// 	// printf("|%s| < -- III \n", after);

// 	before = ft_strjoin(before, main);
// 	before = ft_strjoin(before, after);

// 	// printf("%s\n", before);
// 	return (before);
// }

