/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/14 23:15:52 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  (мои друзья)    ''  ""  \   $  |  > < >> <<  (мои друзья)

static void	initMyString(t_str *str, char *input)
{
	int i;

	i = 0;
	str->input = ft_strdup(input);
	str->buf = NULL;
	str->quote = 0;
	str->ecran = 0;
	str->dub_quote = 0;
	str->dollars = 0;
	str->iter = 0;

	while (input[i])
	{
		if (input[i] == '\'')
			str->quote += 1;
		else if (input[i] == '\"')
			str->dub_quote += 1;
		else if (input[i] == '$')
			str->dub_quote += 1;
		else if (input[i] == '\\')
			str->dub_quote += 1;
		i++;
	}
	
}

static char *preparse(char *input, t_all *all)
{
	t_str	*myString;
	
	(void) all;
	myString = malloc(sizeof(t_str));
	initMyString(myString, input);
	if (myString->quote || myString->dub_quote || myString->dollars || myString->ecran)
	{
		while (myString->input[myString->iter])
		{
			if (myString->input[myString->iter] == '\'')
				myString->buf = ft_quote(myString);
			myString->iter++;
		}
	}
	else
		myString->buf = myString->input;
	return (myString->buf);
}

int	parse(t_all *all, char *input)
{
	char		*parse_input;
	t_list		*HEAD;

	parse_input = preparse(input, all);
	printf("|%s|\n", parse_input);
	parse_path(all);
	HEAD = make_list_with_all_word(parse_input);
	all->number_command = num_of_commands(HEAD, all);
	init_cmd_struct(all);
	fill_cmd_struct(all, HEAD);

	return 0;
}


