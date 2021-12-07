/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:24:20 by bshawn            #+#    #+#             */
/*   Updated: 2021/11/25 20:15:54 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int ft_makelist(t_all *all, char *ready_str)
{
	if (!ft_strcmp(ready_str, "cd"))
		all->cmd[all->i]->arg = ft_lstnew("cd");
	else if (!ft_strcmp(ready_str, "echo"))
		all->cmd[all->i]->arg = ft_lstnew("echo");
	else if (!ft_strcmp(ready_str, "pwd"))
		all->cmd[all->i]->arg = ft_lstnew("pwd");
	else if (!ft_strcmp(ready_str, "ls"))
		all->cmd[all->i]->arg = ft_lstnew("ls");
	else if (!ft_strcmp(ready_str, "wc"))
		all->cmd[all->i]->arg = ft_lstnew("wc");
	else if (!ft_strcmp(ready_str, "export"))
		all->cmd[all->i]->arg = ft_lstnew("export");
	else if (!ft_strcmp(ready_str, "unset"))
		all->cmd[all->i]->arg = ft_lstnew("unset");
	else if (!ft_strcmp(ready_str, "env"))
		all->cmd[all->i]->arg = ft_lstnew("env");
	else if (!ft_strcmp(ready_str, "cat"))
		all->cmd[all->i]->arg = ft_lstnew("cat");
	else if (!ft_strcmp(ready_str, "exit"))
		all->cmd[all->i]->arg = ft_lstnew("exit");
	else
		all->cmd[all->i]->arg = NULL;
	return 0;
}


//  (мои друзья)    ''  ""  \   $  |  > < >> <<  (мои друзья)

static char *ft_quote(char *str, int *i)
{
	char	*before;
	char	*main;
	char	*after;
	int		j;

	j = *i;							// Старт (указатель на ковычку)
	while (str[(*i)++])
		if (str[*i] == '\'')        // Конец (узнали, где ковычка закрывается)
			break;

	before = ft_substr(str, 0, j);
	main = ft_substr(str, j + 1, *i - j - 1);
	after = ft_strdup(str + *i + 1);

	before = ft_strjoin(before, main);
	before = ft_strjoin(before, after);

	printf("%s\n", before);
	return (before);
}

int	parse(t_all *all, char *input)
{
	int		i;

	i = 0;
	(void) all;
	while (input[i++])
	{
		if (input[i] == ' ' || input[i] == '\t') // отсекли все отступы в начале строки
			i++;
		if (input[i] == '\'')
			input = ft_quote(input, &i);
			// printf("%s\n", input + i);
	}
	ft_makelist(all, input);
	return 0;
}
