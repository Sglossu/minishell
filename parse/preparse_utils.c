/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:24:09 by bshawn            #+#    #+#             */
/*   Updated: 2022/01/04 00:31:29 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_dir(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 2)
		return (0);
	while (str[i])
	{
		if (str[i] != '>' && str[i] != '<')
			return (0);
		i++;
	}
	return (1);
}

int	is_ecran(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

int	error_token(void)
{
	g_status = 2;
	ft_putendl_fd("minishell: syntax error near unexpected token `|'",
		STDERR_FILENO);
	return (0);
}

int	is_dir_after_pipe(t_list *head)
{
	t_list	*tmp;
	int		rez;

	tmp = head;
	rez = 0;
	if (tmp && (!ft_strcmp(tmp->val, ">") || !ft_strcmp(tmp->val, "<")
			|| !ft_strcmp(tmp->val, "<<") || !ft_strcmp(tmp->val, ">>")))
		rez++;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->val, "|") && (!ft_strcmp(tmp->next->val, ">")
				|| !ft_strcmp(tmp->next->val, "<")
				|| !ft_strcmp(tmp->next->val, "<<")
				|| !ft_strcmp(tmp->next->val, ">>")))
			rez++;
		tmp = tmp->next;
	}
	return (rez);
}
