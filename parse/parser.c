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

static void	make_list(char *input, t_list *tmp)
{
	int	i;

	i = 0;
	if (input[i] == '|')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup("|")));
	else if (input[i] == '>' && input[i+1] == '>')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(">>")));
	else if (input[i] == '<' && input[i+1] == '<')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup("<<")));
	else if (input[i] == '>')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(">")));
	else if (input[i] == '<')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup("<")));
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
			while (input[j] && input[j] != ' ' && input[j] != '|'
					 && input[j] != '<' && input[j] != '>' )
				j++;
			str = ft_substr(input, i, j - i);
			if (ft_strlen(str) > 0)
				ft_lstadd_back(&tmp, ft_lstnew(str));
			else
				free(str);
			i = j;
			make_list(input + j, tmp);
		}
		i++;
	}

	return(tmp);
}

static	int	num_of_commands(t_list *HEAD, t_all *all)
{
	int		res;
	t_list	*tmp;
	int		pipes;

	res = 0;
	pipes = 1;
	parse_path(all);
	tmp = HEAD;
	while (tmp)
	{
		if ((is_buildin(tmp->val) || is_binary(tmp->val, all)) && pipes)
		{
			res++;
			pipes = 0;
		}
		if (!ft_strcmp(tmp->val, "|"))
			pipes = 1;
		tmp = tmp->next;
	}
	return res;
}

int	init_cmd_struct(t_all *all)
{
	int		i;

	i = 0;
	all->cmd = malloc(sizeof(t_cmd *) * (all->number_command + 1));
	while(i < all->number_command)
	{
		all->cmd[i] = malloc(sizeof(t_cmd));
		i++;
	}
	all->cmd[i] = NULL;
	return (0); 
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

char *path_com(t_all *all, char *command)
{
	int i = 0;
	parse_path(all);
	path_pl_command(all, command);

	while (all->path[i])
	{
		if (!access(all->path[i], 0 | 1))
		{
			return (all->path[i]); // команда нашлась по этому пути
		}
		i++;
	}
	return (NULL);

}

int	fill_cmd_struct(t_all *all, t_list *HEAD)
{
	int		i;
	i = 0;

	while (all->cmd[i])
	{ 
		all->cmd[i]->arg = copy_part_of_list(all, HEAD, i);
		if (is_buildin(all->cmd[i]->arg->val))
		{
			all->cmd[i]->path_command = NULL;
			all->cmd[i]->type = BUILDIN;
		}
		else if (is_binary(all->cmd[i]->arg->val, all))
		{
			all->cmd[i]->path_command = path_com(all ,all->cmd[i]->arg->val);
			if (!(all->cmd[i]->path_command))
				{
					printf("ВНИМАНИЕ! ПРОИЗОШЛА ЧУШЬ!\n");
					exit(777);
				}
			all->cmd[i]->type = BINARY;
		}
		printf("coomand number - %d\n", i+1);
		ft_lstprint(all->cmd[i]->arg);
		i++;		
	}
	return 0;
}

int	parse(t_all *all, char *input)
{
	t_list		*HEAD;

	// parse_path(all);			 пока закоментил, а то адреса накладываются и команды считаются неправильно  //распарсили path
	HEAD = make_list_with_all_word(input);			 // раскдиал слова по односвязному списку (слово1->слово2->слово3)
	all->number_command = num_of_commands(HEAD, all); // посчитал число команд в списке
	init_cmd_struct(all);						// создал структуру кмд (еще не всю)
	fill_cmd_struct(all, HEAD);					// заполнил структуру кмд

	// ft_lstprint(HEAD);								//просто вывод строки по листам
	printf("%d <- commands\n", all->number_command); // вывод числа команд для контроля
	return 0;
}
