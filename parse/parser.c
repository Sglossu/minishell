/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/11/29 20:35:46 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//  (мои друзья)    ''  ""  \   $  |  > < >> <<  (мои друзья)

// static char *ft_quote(char *str, int *i)
// {
// 	char	*before;
// 	char	*main;
// 	char	*after;
// 	int		j;

// 	j = *i;							// Старт (указатель на ковычку)
// 	while (str[(*i)++])
// 		if (str[*i] == '\'')        // Конец (узнали, где ковычка закрывается)
// 			break;

// 	// printf("%d <-j   %d <- i\n", j, *i);
// 	before = ft_substr(str, 0, j);
// 	// printf("|%s| < -- I \n", before);
// 	main = ft_substr(str, j + 1, *i - j - 1);
// 	// printf("|%s| < -- II \n", main);
// 	after = ft_strdup(str + *i + 1);
// 	// printf("|%s| < -- III \n", after);

// 	before = ft_strjoin(before, main);
// 	before = ft_strjoin(before, after);

// 	// printf("%s\n", before);
// 	return (before);
// }

void	ft_lstprint(t_list *HEAD)           // принтит все значения списка
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

static t_list	*make_list_with_all_word(char *input)
{
	int		i;
	int		j;
	t_list	*tmp;
	char	*str;

	i = 0;
	tmp = NULL;
	while(input[i])
	{
		if (input[i] != ' ')
		{
			j = i;
			while (input[j] && input[j] != ' ' && input[j] != '|')
				j++;
			str = ft_substr(input, i, j - i);
			i = j;
			if (ft_strlen(str) > 0)
				ft_lstadd_back(&tmp, ft_lstnew(str));
			else
				free(str);
		}
		i++;
	}

	return(tmp);
}

static	int	num_of_commands(t_list *HEAD, t_all *all)
{
	int		res;
	t_list	*tmp;

	res = 0;
	parse_path(all);
	tmp = HEAD;
	while (tmp)
	{
		if (is_buildin(tmp->val) || is_binary(tmp->val, all))   // я пока не могу посчитать бинарные команды, хочу сделать билдины
			res++;
		tmp = tmp->next;
	}
	return res;
}

int	init_cmd_struct(t_all *all, t_list *HEAD)
{
	t_list	*tmp;
	int		i;

	tmp = HEAD;

	i = 0;
	all->cmd = malloc(sizeof(t_cmd *) * (all->number_command + 1));
	while(i < all->number_command)
	{
		all->cmd[i] = malloc(sizeof(t_cmd));
		i++;
	}
	all->cmd[i] = NULL;

	i = 0;
	while (i != all->number_command)
	{
		all->cmd[i]->arg = tmp;
		all->cmd[i]->type = BUILDIN; // bin or buildin ??????????
		i++;
	}
	return (0); 
}

int	parse(t_all *all, char *input)
{
	t_list		*HEAD;

	parse_path(all);
	HEAD = make_list_with_all_word(input);
	
	all->number_command = num_of_commands(HEAD, all);                      // пока только билдины
	init_cmd_struct(all, HEAD);

	
	
	
	ft_lstprint(HEAD);
	printf("%d <- commands\n", all->number_command);
	return 0;
}
