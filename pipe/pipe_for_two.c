#include "../includes/minishell.h"

void second_pipe(t_all *all, int fd[2])
{
	all->i = 1;
	all->cmd[1]->pid = fork();
	if (all->cmd[1]->pid < 0)
	{
		s_status = errno;
		ft_putendl_fd(strerror(errno), 2);
	}
	if (all->cmd[1]->pid == 0)
	{
		ft_signal_in_child();
		if (dup2(fd[0], STDIN_FILENO) == -1) // теперь stdin (ввод) это как fd[0]
		{
			s_status = errno;
			exit(errno);
		}
		close(fd[1]);
		close(fd[0]);
		main_function_for_one_direct(all);
		if (if_buildins(&all->env, all->exp, all->cmd[all->i]->arg))
			child(all, 1);
		exit (s_status);
	}
}

void	first_pipe(t_all *all, int fd[2])
{
	all->cmd[0]->pid = fork();
	if (all->cmd[0]->pid < 0)
	{
		s_status = errno;
		ft_putendl_fd(strerror(errno), 2);
	}
	if (all->cmd[0]->pid == 0)
	{
		ft_signal_in_child();
		if(dup2(fd[1], STDOUT_FILENO) == -1) // делает stdout (вывод) копией fd[1], теперь stdout это как fd[1]
		{
			s_status = errno;
			exit(errno);
		}
		close(fd[0]);
		close(fd[1]);
		main_function_for_one_direct(all);
		if (if_buildins(&all->env, all->exp, all->cmd[0]->arg))
			child(all, 0);
		exit(s_status);
	}
}

int pipe_for_two(t_all *all, int *status)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		s_status = errno;
		return(errno);
	}
	first_pipe(all, fd);
	second_pipe(all, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(all->cmd[0]->pid, status, 0);
	waitpid(all->cmd[1]->pid, status, 0);
	ft_signal_main();
	return (0);
}
