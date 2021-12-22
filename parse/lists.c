/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:15:33 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:15:35 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstprint(t_list *HEAD)
{
	t_list	*tmp;
	int		count;

	tmp = HEAD;
	count = 1;
	while (tmp)
	{
		printf("|%s| - arg %d\n", tmp->val, count);
		count++;
		tmp = tmp->next;
	}
}

static void	make_part_direct_pipe(char *input, t_list **tmp, int *i)
{
	if (input[*i] == '|')
		ft_lstadd_back(tmp, ft_lstnew(ft_strdup("|")));
	else if (input[*i] == '>' && input[*i+1] == '>')
	{
		ft_lstadd_back(tmp, ft_lstnew(ft_strdup(">>")));
		*i += 1;
	}
	else if (input[*i] == '<' && input[*i+1] == '<')
	{
		ft_lstadd_back(tmp, ft_lstnew(ft_strdup("<<")));
		*i += 1;
	}
	else if (input[*i] == '>')
		ft_lstadd_back(tmp, ft_lstnew(ft_strdup(">")));
	else if (input[*i] == '<')
		ft_lstadd_back(tmp, ft_lstnew(ft_strdup("<")));
}

// static void make_part_quote(char *input, t_list **tmp, int *i)
// {
// 	char	*str;
// 	int		j;
// 	char	sym;

// 	sym = input[*i];
// 	j =  *i + 1;
// 	while (input[j] && input[j] != sym)
// 		j++;
// 	str = ft_substr(input, *i, j - *i + 1);
// 	if (ft_strlen(str) > 0)
// 		ft_lstadd_back(tmp, ft_lstnew(str));
// 	else
// 		free(str);
// 	*i = j;
// }

static void make_part_world(char *input, t_list **tmp, int *i)
{
	char	*str;
	char	sym;
	int		j;
	
	j = *i;
	while (input[j] && input[j] != ' ' && input[j] != '>' && input[j] != '<' && input[j] != '|')
	{
		if (input[j] == '\'' || input[j] == '\"')
		{
			
			sym = input[j++];
			// printf("%c\n", sym);
			while (input[j] && input[j] != sym)
				j++;
			j += 1;
			break;
		}
		j++;
	}

	str = ft_substr(input, *i, j - *i);
	// printf("|%s|\n", str);

	if (ft_strlen(str) > 0)
		ft_lstadd_back(tmp, ft_lstnew(str));
	else
		free(str);
	*i = j - 1;
}

t_list	*make_list_with_all_word(char *input)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = NULL;
	while(input[i])
	{
		if (input[i] != ' ')
		{
			if (input[i] == '>' || input[i] == '<' || input[i] == '|')
				make_part_direct_pipe(input, &tmp, &i);
			else
				make_part_world(input, &tmp, &i);
		}
		i++;
	}
	return(tmp);
}

t_list	*copy_part_of_list(t_all *all, t_list *HEAD, int num_command)
{
	t_list	*tmp;
	t_list	*res;
	tmp = HEAD;
	res = NULL;

	(void) all;

	while (num_command)
	{
		if (!ft_strcmp(tmp->val, "|"))
			num_command--;
		tmp = tmp->next;
	}
	while (tmp && ft_strcmp(tmp->val, "|"))
	{
		ft_lstadd_back(&res, ft_lstnew(ft_strdup(tmp->val)));
		tmp = tmp->next;
	}
	return(res);
}
