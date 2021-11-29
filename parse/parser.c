/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/11/29 18:50:43 by bshawn           ###   ########.fr       */
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

void	ft_lstprint(t_list *HEAD)
{
	t_list	*tmp;
	int		i;

	tmp = HEAD;
	i = 0;
	while (tmp)
	{
		printf("%s <-- arg %d\n", tmp->val, i);
		i++;
		tmp=tmp->next;
	}
	
}

static	char	*del_space(char *str)
{
	char	*res;
	int		i;
	int		range;

	i = 0;
	range = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[range])
		range++;	
	
	res = ft_substr(str, i, range - i);
	free(str);
	return(res);
}

static void		add_command_to_list(t_all *all, char *input)
{
	int	i = 0;
	t_list	*HEAD;
	char	*str;

	HEAD = all->cmd[all->i]->arg;
	while (input[i] && (ft_isalpha(input[i]) || input[i] == '-'))
		i++;
	str = ft_substr(input, 0, i);
	ft_lstadd_back(&HEAD, ft_lstnew(str));
	
}

static char		*del_prev_command(char *input)
{
	int		i = 0;
	char	*n_str;

	while (input[i] && (ft_isalpha(input[i]) || input[i] == '-'))
		i++;
	n_str = ft_substr(input, i, ft_strlen(input) - i);
	free(input);
	return(n_str);
}

int	parse(t_all *all, char *input)
{
	int		i;
	// char	*tmp;

	(void) all;
	i = 0;
	

	while (input[i])
	{
		input = del_space(input);
		add_command_to_list(all, input);
		input = del_prev_command(input);
		i++;
	}
	ft_lstprint(all->cmd[all->i]->arg);
	return 0;
}
