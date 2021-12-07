//
// Created by Александра on 06.12.2021.
//

#include "../includes/minishell.h"

int ft_dir(t_cmd *cmd, int fd_std)
{
	int		fd_file;

	fd_file = open(cmd->name_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd_file == -1)
		return (1); // todo ошибка
	if (dup2(fd_file, fd_std) == -1)
		return (1); // todo
	close(fd_file);
	return (0);
}

int ft_doubledir(t_cmd *cmd, int fd_std)
{
	int		fd_file;

	fd_file = open(cmd->name_file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd_file == -1)
		return (1); // todo ошибка
	dup2(fd_file, fd_std);
	close(fd_file);
	return (0);
}

int ft_redir(t_cmd *cmd, int fd_std)
{
	int		fd_file;

	fd_file = open(cmd->name_file, O_RDONLY);
	if (fd_file == -1)
		return (1); // todo ошибка
	dup2(fd_file, fd_std);
	close(fd_file);
	return (0);
}

int ft_doubleredir(t_cmd *cmd, int fd_std, int fd_0)
{
	int		i;
	char	*line;

	line = NULL;
	i = get_next_line(fd_std, &line);
	if (!i || !ft_strcmp(line, cmd->name_file))
		i = 0;
	while (i)
	{
		i = get_next_line(fd_std, &line);
		ft_putstr_fd(line, fd_0);
		if (!i || !ft_strcmp(line, cmd->name_file))
			i = 0;
	}
	free(line);
	return (0);
}

int one_direct(t_all *all)
{
	int status;
	int fd[2];

	if (pipe(fd) == -1)
		return 1; // todo error
	all->cmd[0]->pid = fork();
	if (all->cmd[0]->pid == 0)
	{
		if (all->cmd[0]->f_direct == DIR)
			ft_dir(all->cmd[0], STDOUT_FILENO);
		else if (all->cmd[0]->f_direct == DOUB_DIR)
			ft_doubledir(all->cmd[0], STDOUT_FILENO);
		else if (all->cmd[0]->f_direct == REDIR)
			ft_redir(all->cmd[0], STDIN_FILENO);
		else if (all->cmd[0]->f_direct == DOUB_REDIR)
		{
			ft_doubleredir(all->cmd[0], STDIN_FILENO, fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
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