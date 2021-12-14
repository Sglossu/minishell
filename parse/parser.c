/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/14 20:08:18 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  (мои друзья)    ''  ""  \   $  |  > < >> <<  (мои друзья)

static void	initMyString(t_str *str, char *input)
{
	int i;

	i = 0;
	str = malloc(sizeof(t_str));
	str->input = input;
	str->quote = 0;
	str->dub_quote = 0;
	str->dollars = 0;

	while (input[i])
	{
		if (input[i] == '\'')
			str->quote += 1;
		else if (input[i] == '\"')
			str->dub_quote += 1;
		else if (input[i] == '$')
			str->dub_quote += 1;
		i++;
	}
	
}

static char *preparse(char *input, t_all *all)
{
	t_str	*myString;
	int		i;


	initMyString(myString, input);
	i = 0;
	while (input[i])
	{
		// printf("|%d|<-- i \n", i);
		if (input[i] == '\'')
			input = ft_quote(input, &i);
		if (input[i] == '\"')
			input = ft_dubquoute(input, &i, all);
		// if (input[i] == '$')
		// 	input = ft_dollar(input, all, &i);
		i++;
	}
	return (input);
}

int	parse(t_all *all, char *input)
{
	char		*parse_input;
	t_list		*HEAD;

	parse_input = preparse(input, all);
	parse_path(all);
	HEAD = make_list_with_all_word(parse_input);
	all->number_command = num_of_commands(HEAD, all);
	ft_lstprint(HEAD);
	init_cmd_struct(all);
	fill_cmd_struct(all, HEAD);

	return 0;
}


