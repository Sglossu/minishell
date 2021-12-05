//
// Created by Александра on 05.12.2021.
//

#include "../includes/minishell.h"

int one_with_direct(t_all *all)
{
	int status;

	all->cmd[0]->pid = fork();
	if (all->cmd[0]->pid == 0)
	{
		if (all->cmd[0]->f_direct == DIR)
			f_l_dir(all->cmd[0], STDOUT_FILENO);
		else if (all->cmd[0]->f_direct == DOUBLE_DIR)
			f_l_doubledir(all->cmd[0], STDOUT_FILENO);
		else if (all->cmd[0]->f_direct == REDIR)
			f_l_redir(all->cmd[0], STDIN_FILENO);
		if (if_buildins(&all->env, all->cmd[0]->arg))
			child(all, 0);
		exit(0);
	}
	else
	{
		waitpid(all->cmd[0]->pid, &status, 0);
	}
	return (0);
}