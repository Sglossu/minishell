/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_for_direct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:17:47 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:17:52 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_dir(t_cmd *cmd, int fd_std)
{
	int		fd_file;

	fd_file = open(cmd->name_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd_file == -1)
	{
		ft_printf(STDERR_FILENO, "%s: %s\n", cmd->name_file, strerror(errno));
		g_status = errno;
		exit(errno);
	}
	if (dup2(fd_file, fd_std) == -1)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_status = errno;
		exit(errno);
	}
	close(fd_file);
	return (0);
}

int	ft_doubledir(t_cmd *cmd, int fd_std)
{
	int		fd_file;

	fd_file = open(cmd->name_file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd_file == -1)
	{
		ft_printf(STDERR_FILENO, "%s: %s\n", cmd->name_file, strerror(errno));
		g_status = errno;
		exit (errno);
	}
	if (dup2(fd_file, fd_std) == -1)
	{
		close(fd_file);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_status = errno;
		exit (errno);
	}
	close(fd_file);
	return (0);
}

int	ft_redir(t_cmd *cmd, int fd_std)
{
	int	fd_file;

	fd_file = open(cmd->name_file, O_RDONLY);
	if (fd_file == -1)
	{
		ft_printf(STDERR_FILENO, "%s: %s\n", cmd->name_file, strerror(errno));
		g_status = errno;
		exit (errno);
	}
	if_doub_redir(cmd);
	if (!cmd->flag_redirect)
	{
		if (dup2(fd_file, fd_std) == -1)
		{
			close(fd_file);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			g_status = errno;
			exit (errno);
		}
	}
	close(fd_file);
	return (0);
}

int	ft_doubleredir(t_cmd *cmd, int fd_std, int fd_0)
{
	int		i;
	char	*line;

	line = NULL;
	write(STDOUT_FILENO, "> ", 2);
	i = get_next_line(fd_std, &line);
	if (!ft_strcmp(line, cmd->name_file))
	{
		free(line);
		return (0);
	}
	ft_putstr_fd(line, fd_0);
	while (i)
	{
		write(STDOUT_FILENO, "> ", 2);
		i = get_next_line(fd_std, &line);
		if (!ft_strcmp(line, cmd->name_file))
			break ;
		ft_putchar_fd('\n', fd_0);
		ft_putstr_fd(line, fd_0);
	}
	ft_putchar_fd('\n', fd_0);
	free(line);
	return (0);
}
