/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/29 20:13:09 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  (мои друзья)  ''  ""  \   $  |  > < >> <<  (мои друзья)

static int	flag_check(t_list *tmp)
{
	char	*str;

	str = tmp->val;
	if (!ft_strcmp(str, "|"))
		return PIPE;
	if (isDir(str))
		return DIRECT;
	return TEXT;
}

static int	preparse(t_all *all, t_list **HEAD, char *input)
{
	t_list	*tmp;
	
	// if (preparse_valid(input))
	// 	return 1;
	*HEAD = make_list_with_all_word(input);
	tmp = *HEAD;
	while (tmp)
	{
		tmp->flag = flag_check(tmp);
		if (tmp->flag == TEXT)
			tmp->val = ready_string(tmp, all);
		if (ft_strlen(tmp->val) == 0)
			ft_lstremove(HEAD, tmp);
		tmp = tmp->next;
	}
	return (0);
}

int	parse(t_all *all, char *input)
{
	t_list		*HEAD;
	int			res;

	all->i = 0;
	res = 0;
	HEAD = NULL;
	if (preparse(all, &HEAD, input))
		return 1;
	ft_lstprint(HEAD);
	num_of_commands(all, HEAD);
	if (!all->number_command && HEAD && isDir(HEAD->val))
		all->number_command++;
	init_cmd_struct(all);
	if (fill_cmd_struct(all, HEAD))
		res = 1;
	ft_lstclear(&HEAD, free);
	return res;
}