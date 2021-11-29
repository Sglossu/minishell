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


// static int ft_makelist(t_all *all, char *ready_str)
// {
// 	if (!ft_strcmp(ready_str, "cd"))
// 		all->cmd[all->i]->arg = ft_lstnew("cd");
// 	else if (!ft_strcmp(ready_str, "echo"))
// 		all->cmd[all->i]->arg = ft_lstnew("echo");
// 	else if (!ft_strcmp(ready_str, "pwd"))
// 		all->cmd[all->i]->arg = ft_lstnew("pwd");
// 	else if (!ft_strcmp(ready_str, "ls"))
// 		all->cmd[all->i]->arg = ft_lstnew("ls");
// 	else if (!ft_strcmp(ready_str, "export"))
// 		all->cmd[all->i]->arg = ft_lstnew("export");
// 	else if (!ft_strcmp(ready_str, "unset"))
// 		all->cmd[all->i]->arg = ft_lstnew("unset");
// 	else if (!ft_strcmp(ready_str, "env"))
// 		all->cmd[all->i]->arg = ft_lstnew("env");
// 	else if (!ft_strcmp(ready_str, "exit"))
// 		all->cmd[all->i]->arg = ft_lstnew("exit");
// 	else
// 		all->cmd[all->i]->arg = NULL;
// 	return 0;
// }


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
	int		i;

	tmp = HEAD;
	i = 0;
	while (tmp)
	{
		printf("|%s| <-- arg %d\n", tmp->val, i);
		i++;
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
	tmp = ft_lstnew(input);
	while(input[i])
	{
		if (input[i] && input[i] != ' ')
		{
			j = i;
			while (input[j] && input[j] != ' ' && input[j] != '|')
				j++;
			str = ft_substr(input, i, j-i);
			i = j;
			// printf("|%s| arg\n", str);
			ft_lstadd_back(&tmp, ft_lstnew(str));
		}
		i++;
	}

	return(tmp);
}

static	int	num_of_commands(t_list *HEAD)
{
	int		res;
	t_list	*tmp;
	char	*input;
	int		i;
	int		pipes_count;

	tmp = HEAD;
	input = tmp->val; // полная строка ВВОДА
	i = 0;
	res = 0;
	pipes_count = 0;
	tmp = tmp->next; // т.к первый лист это полная строка
	while (tmp)
	{
		if ((!ft_strcmp(tmp->val, "cd")) || (!ft_strcmp(tmp->val, "pwd")) || (!ft_strcmp(tmp->val, "echo"))
			|| (!ft_strcmp(tmp->val, "ls")) || (!ft_strcmp(tmp->val, "export")) || (!ft_strcmp(tmp->val, "unset"))
				|| (!ft_strcmp(tmp->val, "env")) || (!ft_strcmp(tmp->val, "exit")) || (!ft_strcmp(tmp->val, "cat")))
				res++;
		tmp = tmp->next;
	}

	// while (input[i++])                  // Может быть проблема, т.к команды без пайпов - мусорные слова, которые командами не являются
	// 	if (input[i] == '|')
	// 		pipes_count++;
	
	// if (res - 1 != pipes_count)			// потом придум0аю как это проверить

	return res;
}

int	parse(t_all *all, char *input)
{
	t_list		*HEAD;

	(void) 		all;
	
	HEAD = make_list_with_all_word(input); 
	all->number_command = num_of_commands(HEAD);

	ft_lstprint(HEAD);
	printf("%d < --- commands\n", all->number_command);
	return 0;
}
