//
// Created by Shasta Glossu on 12/8/21.
//

# include "../includes/minishell.h"

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
	ft_putstr_fd(line, fd_0);
	while (i)
	{
		write(0, "> ", 2);
		i = get_next_line(fd_std, &line);
		if (!ft_strcmp(line, cmd->name_file))
			break;
		ft_putstr_fd(line, fd_0);
	}
	ft_putchar_fd('\n', fd_0);
	free(line);
	return (0);
}
