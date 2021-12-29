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
		return 1;
	*HEAD = make_list_with_all_word(input);
	tmp = *HEAD;
	while (tmp)
	{
		tmp->flag = flag_check(tmp);
		if (tmp->flag == TEXT)
			tmp->val = ready_string(tmp, all);
		tmp = tmp->next;
	}
	return (0);
}

int	parse(t_all *all, char *input)
{
	t_list		*HEAD;

	all->i = 0;
	HEAD = NULL;
	if (preparse(all, &HEAD, input))
		return 1;

	num_of_commands(all, HEAD); // тут лик


	if (!all->number_command && HEAD && isDir(HEAD->val))
		all->number_command++;

	init_cmd_struct(all);

//	ft_lstprint(HEAD);

	if (fill_cmd_struct(all, HEAD))
		return 1;
	return 0;
}