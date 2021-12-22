/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/17 00:44:11 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  (мои друзья)  ''  ""  \   $  |  > < >> <<  (мои друзья)

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

static int preparse_valid(t_str *str)
{
	if (str->dub_quote % 2 != 0)
		return 1; // ковычки не закрыты
	if (str->dub_quote % 2 != 0)
		return 1; // двойные ковычки не закрыты

	return 0; // все в порядке
}

static int	preparse(t_all *all, t_list **HEAD, char *input)
{
	t_str	*myString;
	int		status;
	(void) all;
	
	myString = malloc(sizeof(t_str));
	initMyString(myString, input);
	status = preparse_valid(myString);
	if (status)
		return 1;

	*HEAD = make_list_with_all_word(input);
	// if (myString->quote || myString->dub_quote || myString->dollars || myString->ecran)
	// {
	// 	while (myString->input[myString->iter])
	// 	{
	// 		if (myString->input[myString->iter] == '\''
	// 		 || myString->input[myString->iter] == '\"')
	// 			myString->input = ft_quote(myString, myString->input[myString->iter]);
	// 		myString->iter++;
	// 	}
	// }
	return (0);
}

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
	t_list		*HEAD;
	int			status;

	HEAD = NULL;
	status = preparse(all, &HEAD, input);
	if (status)
		return 1;

	ft_lstprint(HEAD);
	num_of_commands(all, HEAD);
	init_cmd_struct(all);
	fill_cmd_struct(all, HEAD);
	
	return 0;
}


