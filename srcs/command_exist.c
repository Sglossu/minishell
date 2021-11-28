//
// Created by Shasta Glossu on 11/25/21.
//

#include "../includes/minishell.h"

int parse_path(t_all *all)
{
	t_list	*tmp;
	int		i = 0;
	char 	*str;

	tmp = ft_lstfind(all->env, "PATH");
	if (!tmp)
		return (1); // todo обработать ошибку если нет PATH
	all->path = ft_split(find_after_equals(tmp->val), ':');
	if (!all->path)
		return (1); // todo обработать ошибку
	while (all->path[i])
	{
		if (all->path[i][0] == '~')
		{
			str = ft_strdup(all->path[i] + 1);
			free(all->path[i]);
			tmp = ft_lstfind(all->env, "HOME");
			if (!tmp)
				return (1); // todo обработать ошибку если нет HOME
			all->path[i] = ft_strjoin(find_after_equals(tmp->val), str);
			free(str);
		}
		i++;
	}
	return (0);
}

//void path_print(t_all *all)
//{
//	int i = 0;
//
//	while (all->path[i])
//	{
//		printf("%s\n", all->path[i]);
//		i++;
//	}
//}

void	path_plus_command(t_all *all)
{
	int 	i = 0;
	char 	*str1;
	char 	*str2;

	while (all->path[i])
	{
		str1 = ft_strdup(all->path[i]);
		free(all->path[i]);
		str2 = ft_strjoin("/", all->cmd[all->i]->arg->val);
		all->path[i] = ft_strjoin(str1, str2);
		free(str2);
		free(str1);
		i++;
	}
}

int find_command(t_all *all)
{
	int i = 0;

	while (all->path[i])
	{
		if (!access(all->path[i], 0 | 1))
		{
			all->cmd[all->i]->path_command = ft_strdup(all->path[i]);
			return (0); // команда нашлась по этому пути
		}
		i++;
	}
	return (1); // не нашел такой команды нигде
}

int if_command_exist(t_all *all)
{
	if (parse_path(all))
		return (1); // todo обработать ошибку
	path_plus_command(all);
	find_command(all);
//	path_print(all);
	return (0);
}