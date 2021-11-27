//
// Created by Shasta Glossu on 11/27/21.
//

#include "../includes/minishell.h"

int our_pipe(t_all **all)
{
	int		fd[2];
	pid_t	pid1;
	pid_t 	pid2;

	if (pipe(fd) == -1)
		return (1); // todo обработать ошибку
	pid1 = fork();
	if (pid1 < 0)
		return (2); // todo обработать ошибку

	if_command_exist(all); // путь для 1 команды записывается в переменную
	if (pid1 == 0)
	{
		// child process 1 (ls)
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO); // делает stdout (вывод) копией fd[1], теперь stdout это как fd[1]
		close(fd[1]);
		child(all);
	}

	pid2 = fork();
	free((*all)->arg);
	(*all)->arg = ft_lstnew(ft_strdup("cat"));
	if_command_exist(all); // путь для команды 2 записывается в переменную

	if (pid2 < 0)
		return (3); // todo обработать ошибку
	if (pid2 == 0)
	{
		// child process 2 (wc)
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO); // теперь stdin (ввод) это как fd[0]
		close(fd[0]);
		child(all);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}