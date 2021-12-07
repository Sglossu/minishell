#include "../includes/minishell.h"

int	ft_free(t_all *all)
{
	int	i;

	i = 0;

	while(all->cmd[i])
	{
		free(all->cmd[i]);
		i++;
	}
	free(all->cmd);
	all->cmd = NULL; // тестовый вариант
	all->number_command = 0;
	all->i = 0;
	return (0);
}