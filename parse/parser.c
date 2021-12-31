/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/31 19:56:52 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  (мои друзья)  ''  ""  \   $  |  > < >> <<  (мои друзья)
static int	flag_check(t_list *tmp, t_all *all, int *pipe)
{
	char	*str;

	str = tmp->val;
	if (!ft_strcmp(str, "|"))
	{
		*pipe = 1;
		return (PIPE);
	}
	if (is_dir(str))
	{
		*pipe = 0;
		return (DIRECT);
	}
	if (pipe)
	{
		if (is_buildin(tmp->val) || is_binary(tmp->val, all))
		{
			*pipe = 0;
			return (COMMAND);
		}
		else
		{
			*pipe = 0;
			return (WTF);
		}
	}
	*pipe = 0;
	return (TEXT);
}

static int	preparse(t_all *all, t_list **head, char *input)
{
	t_list	*tmp;
	int		flag;
	int		pipe;

	flag = 0;
	pipe = 1;
	*head = make_list_with_all_word(input);
	tmp = *head;
	while (tmp)
	{
		tmp->flag = flag_check(tmp, all, &pipe);
		if (tmp->flag == TEXT || tmp->flag == COMMAND || tmp->flag == WTF)
		{
			tmp->val = ready_string(tmp, all, &flag);
			if (!tmp->val)
			{
				g_status = errno;
				return (0);
			}
		}
		if (ft_strlen(tmp->val) == 0 && (!flag))
			ft_lstremove(head, tmp);
		tmp = tmp->next;
		flag = 0;
	}
	return (1);
}

int	parse(t_all *all, char *input)
{
	t_list		*head;
	int			res;
	int			flag;

	all->i = 0;
	res = 0;
	flag = 0;
	head = NULL;
	if (!preparse(all, &head, input))
		return (1);
	flag = num_of_commands(all, head);
	if (flag == 0)
	{
		if (!all->number_command && head && is_dir(head->val))
			all->number_command++;
		init_cmd_struct(all);
		if (fill_cmd_struct(all, head))
			res = 0;
		ft_lstclear(&head, free);
	}
	else
		res = 1;
	return (res);
}
