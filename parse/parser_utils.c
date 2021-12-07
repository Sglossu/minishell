#include "../includes/minishell.h"

void	path_pl_command(t_all *all, char *command)
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
	parse_path(all);
	path_pl_command(all, val);
	return(find_com(all));
}

int is_buildin(char *val)             // проверка билдина
{
	if ((!ft_strcmp(val, "cd")) || (!ft_strcmp(val, "pwd")) || (!ft_strcmp(val, "echo"))
			|| (!ft_strcmp(val, "export")) || (!ft_strcmp(val, "unset"))
				|| (!ft_strcmp(val, "env")) || (!ft_strcmp(val, "exit")))
		return 1;
	else
		return 0;
}