//
// Created by Shasta Glossu on 11/27/21.
//

#include "../includes/minishell.h"

void	child_for_pipe(t_all *all, int i, int com, int fd[com][2])
{
	// i - номер команды, com - общее количество пайпов
	int k = 0;

	if (i == 0) // i - номер команды
		first_last_pipe(all->cmd[0], fd[0][1], STDOUT_FILENO); // первая команда
	else if (i == com)
		first_last_pipe(all->cmd[i], fd[com - 1][0], STDIN_FILENO); // последняя
	else
		middle_pipe(all->cmd[i - 1], fd[i - 1][0], fd[i][1]);
	while (k < com)
	{
		close(fd[k][0]);
		close(fd[k][1]);
		k++;
	}
	if (if_buildins(&all->env, all->cmd[i]->arg))
		child(all, i);
}

int pipe_for_another(t_all *all, int com, int *status) // com - количество пайпов
{
	int 	fd[com][2];
	pid_t	pid[com + 1];
	int 	i = 0;

	while (i < com)
	{
		if (pipe(fd[i]) == -1)
			return (1); // todo обработать ошибку
		i++;
	}
	i = 0;
	while (i < com + 1)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			child_for_pipe(all, i, com, fd); // i - номер дочернего процесса, т. е. номер команды
		}
		i++;
	}
	i = 0;
	while (i < com)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < com + 1)
	{
		waitpid(pid[i], status, 0);
		i++;
	}
	return (0);
}

int pipe_for_two(t_all *all, int *status)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		return (1); // todo обработать ошибку
	pid[0] = fork();
	if (pid[0] < 0)
		return (2); // todo обработать ошибку
	if (pid[0] == 0)
	{
		first_last_pipe(all->cmd[0], fd[1], STDOUT_FILENO); // внутри dup2
		close(fd[0]);
		close(fd[1]);
		child(all, 0);
	}
	pid[1] = fork();
	all->i = 1;
	if (pid[1] < 0)
		return (3); // todo обработать ошибку
	if (pid[1] == 0)
	{
		first_last_pipe(all->cmd[1], fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		child(all, 1);
	}
	close(fd[0]);
	close(fd[1]);

	waitpid(pid[0], status, 0);
	waitpid(pid[1], status, 0);
	return (0);
}

int our_pipe(t_all *all)
{
	int status = 0;
	if (all->number_command == 2)
	{
<<<<<<< HEAD
		if_command_exist(all);

		all->i++;
		all->cmd[all->i]->arg = ft_lstnew(ft_strdup("wc"));
		if_command_exist(all);

=======
		// ИГОРЬ, СЧИТАЙ ЧТО НИЖЕ ПРОСТО НАПИСАН МЕЙНИК ДЛЯ ПАЙПОВ И РЕДИРЕКТОВ, ПОКА НЕТ ПАРСЕРА
		if_command_exist(all); // путь для 1 команды записывается в переменную
		all->cmd[all->i]->f_direct = DIR;
		all->cmd[all->i]->name_file = ft_strdup("2");
//		ft_lstadd_back(&all->cmd[all->i]->arg, ft_lstnew(ft_strdup(">")));
//		ft_lstadd_back(&all->cmd[all->i]->arg, ft_lstnew(ft_strdup("2")));
		all->i++;
		all->cmd[all->i]->arg = ft_lstnew(ft_strdup("cat"));
		all->cmd[all->i]->f_direct = REDIR;
		all->cmd[all->i]->name_file = ft_strdup("2");
//		ft_lstadd_back(&all->cmd[all->i]->arg, ft_lstnew(ft_strdup("<")));
//		ft_lstadd_back(&all->cmd[all->i]->arg, ft_lstnew(ft_strdup("2")));
		if_command_exist(all); // путь для 2 команды записывается в переменную
>>>>>>> 973fa81f5b1b4ed802e81d0bcbe10ff5ba864eb5
		all->i = 0;
		return(pipe_for_two(all, &status));
	}
	else
	{
<<<<<<< HEAD
		if_command_exist(all); // путь для 1 команды записывается в переменную

		all->i++;
		all->cmd[all->i]->arg = ft_lstnew(ft_strdup("wc"));
		if_command_exist(all); // путь для 2 команды записывается в переменную

		all->i++;
		all->cmd[all->i]->arg = ft_lstnew(ft_strdup("cat"));
		if_command_exist(all); // путь для 3 команды записывается в переменную

		all->i++;
		all->cmd[all->i]->arg = ft_lstnew(ft_strdup("wc"));
		if_command_exist(all); // путь для 4 команды записывается в переменную
=======
		// ИГОРЬ, СЧИТАЙ ЧТО НИЖЕ ПРОСТО НАПИСАН МЕЙНИК ДЛЯ ПАЙПОВ И РЕДИРЕКТОВ, ПОКА НЕТ ПАРСЕРА
		if_command_exist(all);
		all->cmd[all->i]->f_direct = DIR;
		all->cmd[all->i]->name_file = ft_strdup("2");

		all->i++;
		all->cmd[all->i]->arg = ft_lstnew(ft_strdup("env"));
		if_command_exist(all);

		all->i++;
		all->cmd[all->i]->arg = ft_lstnew(ft_strdup("wc"));
//		all->cmd[all->i]->f_direct = REDIR;
//		all->cmd[all->i]->name_file = ft_strdup("3");
		if_command_exist(all);
>>>>>>> 973fa81f5b1b4ed802e81d0bcbe10ff5ba864eb5

		all->i++;
		all->cmd[all->i]->arg = ft_lstnew(ft_strdup("cat"));
		if_command_exist(all);

		all->i = 0;
		return(pipe_for_another(all, all->number_command - 1, &status));
	}
	return (0);
}