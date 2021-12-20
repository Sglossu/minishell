/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/14 18:15:49 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  (мои друзья)    ''  ""  \   $  |  > < >> <<  (мои друзья)

// static char *preparse(char *input)
// {
// 	int		i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		// printf("|%d|<-- i \n", i);
// 		if (input[i] == '\'')
// 			input = ft_quote(input, &i);
// 		// if (input[i] == '\"')
// 		// 	res = ft_dubquoute(input, &i);
// 		// if (input[i] == '$')
// 		// 	res = ft_dollar(input, &i);
// 		i++;
// 	}
// 	return (input);
// }

int	parse(t_all *all, char *input)
{
	char		*parse_input;
	t_list		*HEAD;

	// parse_input = preparse(input);
	parse_input = input;
	parse_path(all);
	HEAD = make_list_with_all_word(parse_input);
	all->number_command = num_of_commands(HEAD, all);
	ft_lstprint(HEAD);
	init_cmd_struct(all);
	fill_cmd_struct(all, HEAD);

	return 0;
}


