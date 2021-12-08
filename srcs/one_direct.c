//
// Created by Александра on 06.12.2021.
//

#include "../includes/minishell.h"

int main_function_for_one_direct(t_all *all)
{
	int fd[2];


	if (pipe(fd) == -1)
		return 1; // todo error

	if (all->cmd[all->i]->f_direct == DIR)
		ft_dir(all->cmd[all->i], STDOUT_FILENO);
	else if (all->cmd[all->i]->f_direct == DOUB_DIR)
		ft_doubledir(all->cmd[all->i], STDOUT_FILENO);
	else if (all->cmd[all->i]->f_direct == REDIR)
		ft_redir(all->cmd[all->i], STDIN_FILENO);
	else if (all->cmd[all->i]->f_direct == DOUB_REDIR)
	{
		ft_doubleredir(all->cmd[all->i], STDIN_FILENO, fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	close(fd[0]);
	close(fd[1]);
	if (all->number_command == 1)
	{
		if (if_buildins(&all->env, all->cmd[all->i]->arg))
			child(all, all->i);
	}
	return (0);
}

int one_direct(t_all *all)
{
	int status;

	all->cmd[all->i]->pid = fork();
	if (all->cmd[all->i]->pid == 0)
	{
		main_function_for_one_direct(all);
		exit(0);
	}
	else
	{
		waitpid(all->cmd[all->i]->pid, &status, 0);
	}
	return (0);
}