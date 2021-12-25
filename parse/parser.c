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

// static void	initMyString(t_str *str, char *input)
// {
// 	int i;

// 	i = 0;
// 	str->input = ft_strdup(input);
// 	str->buf = NULL;
// 	str->quote = 0;
// 	str->ecran = 0;
// 	str->dub_quote = 0;
// 	str->dollars = 0;
// 	str->iter = 0;

// 	while (input[i])
// 	{
// 		if (input[i] == '\'')
// 			str->quote += 1;
// 		else if (input[i] == '\"')
// 			str->dub_quote += 1;
// 		else if (input[i] == '$')
// 			str->dub_quote += 1;
// 		else if (input[i] == '\\')
// 			str->dub_quote += 1;
// 		i++;
// 	}
// }

static int preparse_valid(char *str)
{
	int dub_quote;
	int quote;
	int	i;

	i = 0;
	dub_quote = 0;
	quote = 0;

	while (str[i])
	{
		if (str[i] == '\'')
			quote++;
		if (str[i] == '\"')
			dub_quote++;
		i++;
	}

	if (quote || dub_quote)
	{
		if (quote % 2 != 0)
			return 1;
		if (dub_quote % 2 != 0)
			return 1;
	}
	return 0;
}

static int	flag_check(t_list *tmp)
{
	char *str;

	str = ft_strdup(tmp->val);

	if (!ft_strcmp(str, "|"))
		return PIPE;
	if (isDir(str))
		return DIRECT;
	return TEXT;

	free(str);
}

static int	preparse(t_all *all, t_list **HEAD, char *input)
{
	t_list	*tmp;
	
	if (preparse_valid(input))
		return 1; // error
	*HEAD = make_list_with_all_word(input);
	tmp = *HEAD;
	while (tmp)
	{
		tmp->flag = flag_check(tmp);
		if (tmp->flag == TEXT)
			tmp->val = ready_string(tmp, all);
		// printf("|%s| |%d|\n", tmp->val, tmp->flag);
		tmp = tmp->next;

		
	}
	return (0);
}

int	parse(t_all *all, char *input)
{
	t_list		*HEAD;
	int			status;

	HEAD = NULL;
	status = preparse(all, &HEAD, input);
	if (status)
		return 1;

	// ft_lstprint(HEAD);
	num_of_commands(all, HEAD);
	init_cmd_struct(all);
	fill_cmd_struct(all, HEAD);
	
	return 0;
}


