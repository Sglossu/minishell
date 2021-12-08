//
// Created by Александра on 06.12.2021.
//

#include "../includes/minishell.h"

int ft_dir(t_cmd *cmd, int fd_std)
{
	int		fd_file;

//	ft_putendl_fd(cmd->arg->val, 2);

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

//	ft_putendl_fd(cmd->arg->val, 2);
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
	write(0, "> ", 2);
	i = get_next_line(fd_std, &line);
	if (!ft_strcmp(line, cmd->name_file))
	{
		free(line);
		return (0);
	}
	ft_putendl_fd(line, fd_0);
	while (i)
	{
		write(0, "> ", 2);
		i = get_next_line(fd_std, &line);
		if (!ft_strcmp(line, cmd->name_file))
			break;
		ft_putendl_fd(line, fd_0);
	}
	free(line);
	return (0);
}

int main_function_for_one_direct(t_all *all)
{
//	ft_putendl_fd(all->cmd[all->i]->arg->val, 2);
//	ft_putnbr_fd(all->cmd[all->i]->f_direct, 2);

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
		close(fd[0]);
		close(fd[1]);
	}
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
//	int fd[2];
//
//	if (pipe(fd) == -1)
//		return 1; // todo error
	all->cmd[all->i]->pid = fork();
	if (all->cmd[all->i]->pid == 0)
	{
//		if (all->cmd[all->i]->f_direct == DIR)
//			ft_dir(all->cmd[all->i], STDOUT_FILENO);
//		else if (all->cmd[all->i]->f_direct == DOUB_DIR)
//			ft_doubledir(all->cmd[all->i], STDOUT_FILENO);
//		else if (all->cmd[all->i]->f_direct == REDIR)
//			ft_redir(all->cmd[all->i], STDIN_FILENO);
//		else if (all->cmd[0]->f_direct == DOUB_REDIR)
//		{
//			ft_doubleredir(all->cmd[all->i], STDIN_FILENO, fd[1]);
//			dup2(fd[0], STDIN_FILENO);
//			close(fd[0]);
//			close(fd[1]);
//		}
//		if (all->number_command == 1)
//		{
//			if (if_buildins(&all->env, all->cmd[all->i]->arg))
//				child(all, all->i);
//		}
		main_function_for_one_direct(all);
		exit(0);
	}
	else
	{
//		close(fd[0]);
//		close(fd[1]);
		waitpid(all->cmd[all->i]->pid, &status, 0);
	}
	return (0);
}