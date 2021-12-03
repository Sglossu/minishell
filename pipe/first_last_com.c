//
// Created by Александра on 02.12.2021.
//

#include "../includes/minishell.h"

int f_l_dir(t_cmd *cmd, int fd)
{
	int		fd_file;
//	t_list	*tmp;

//	tmp = ft_lstfind(cmd->arg, ">");
	fd_file = open(cmd->name_file, O_CREAT | O_WRONLY, 0777);
	if (fd_file == -1)
		return (1); // todo ошибка
	dup2(fd_file, fd);
	close(fd_file);
	return (0);
}

int f_l_doubledir(t_cmd *cmd, int fd)
{
	int		fd_file;
//	t_list	*tmp;

//	tmp = ft_lstfind(cmd->arg, ">>");
	fd_file = open(cmd->name_file, O_CREAT | O_TRUNC | O_APPEND, 0777);
	if (fd_file == -1)
		return (1); // todo ошибка
	dup2(fd_file, fd);
	close(fd_file);
	return (0);
}

int f_l_redir(t_cmd *cmd, int fd)
{
	int		fd_file;
//	t_list	*tmp;

//	tmp = ft_lstfind(cmd->arg, "<");
	fd_file = open(cmd->name_file, O_RDONLY);
	if (fd_file == -1)
		return (1); // todo ошибка
	dup2(fd_file, fd);
	close(fd_file);
	return (0);
}