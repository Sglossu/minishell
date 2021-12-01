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

static void	path_pl_command(t_all *all, char *command)
{
	int 	i = 0;
	char 	*str1;
	char 	*str2;

	while (all->path[i])
	{
		str1 = ft_strdup(all->path[i]);
		free(all->path[i]);
		str2 = ft_strjoin("/", command);
		all->path[i] = ft_strjoin(str1, str2);
		free(str2);
		free(str1);
		i++;
	}
}

int find_com(t_all *all)
{
	int i = 0;

	while (all->path[i])
	{
		if (!access(all->path[i], 0 | 1))
		{
			return (1); // команда нашлась по этому пути
		}
		i++;
	}
	return (0); // не нашел такой команды нигде
}

int is_binary(char *val, t_all *all)    // проверка бинарника
{
	path_pl_command(all, val);
	return(find_com(all));
}

int is_buildin(char *val)             // проверка билдина
{
	if ((!ft_strcmp(val, "cd")) || (!ft_strcmp(val, "pwd")) || (!ft_strcmp(val, "echo"))
			|| (!ft_strcmp(val, "ls")) || (!ft_strcmp(val, "export")) || (!ft_strcmp(val, "unset"))
				|| (!ft_strcmp(val, "env")) || (!ft_strcmp(val, "exit")))
		return 1;
	else
		return 0;
}

int	ft_free(t_all *all)
{
	//Нам нужно освободить память, которую мы выделяли для CMD и PATH (так как мы их всегда парсим заново)
	int	i;

	i = 0;
	while(i < all->number_command)
	{
		free(all->cmd[i]);
		i++;
	}
	free(all->cmd);
	return (0);
}