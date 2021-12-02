//
// Created by Александра on 02.12.2021.
//

#include "../includes/minishell.h"

int first_last_pipe(t_cmd *cmd, int fd, int fd_std)
{
	int		ret;

	if (cmd->f_direct == DIR)
		ret = f_l_dir(cmd, STDOUT_FILENO);
	else if (cmd->f_direct == DOUBLE_DIR)
		ret = f_l_doubledir(cmd, STDOUT_FILENO);
	else if (cmd->f_direct == REDIR)
		ret = f_l_redir(cmd, STDIN_FILENO);
	else
		ret = dup2(fd, fd_std);
	if (ret)
	{
		printf("%s: %s\n", cmd->arg->val, strerror(errno));
		return (1);
	}
	ft_lstremove(&cmd->arg, ft_lstfind(cmd->arg, ">"));
	ft_lstremove(&cmd->arg, ft_lstfind(cmd->arg, "<"));
	ft_lstremove(&cmd->arg, ft_lstfind(cmd->arg, ">>"));
	return (0);
}

int middle_pipe(t_all *all, int num_com, int com, int fd[com][2])
{
	(void)all;
	dup2(fd[num_com - 1][0], STDIN_FILENO);
	dup2(fd[num_com][1], STDOUT_FILENO);
	return (0);
}

