//
// Created by Александра on 02.12.2021.
//

#include "../includes/minishell.h"

//void	del_after_key(t_list *arg, int f_direct)
//{
//	t_list	*tmp;
//	t_list	*tmp2;
//
//	tmp = NULL;
//	if (f_direct == DIR)
//		tmp = ft_lstfind(arg, ">");
//	else if (f_direct == DOUBLE_DIR)
//		tmp = ft_lstfind(arg, ">>");
//	else if (f_direct == REDIR)
//		tmp = ft_lstfind(arg, "<");
//	while (tmp)
//	{
//		tmp2 = tmp->next;
//		ft_lstremove(&arg, tmp);
//		tmp = tmp2;
//	}
//}

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
//	if (cmd->f_direct != NONE)
//		del_after_key(cmd->arg, cmd->f_direct);
	if (ret)
	{
		printf("%s: %s\n", cmd->arg->val, strerror(errno));
		return (1);
	}
	return (0);
}

int middle_pipe(t_cmd *cmd, int fd_com1, int fd_com2)
{
	int		ret;
	int 	ret2;

	if (cmd->f_direct == DIR)
	{
		ret = f_l_dir(cmd, STDOUT_FILENO);
		ret2 = dup2(fd_com1, STDIN_FILENO);
	}
	else if (cmd->f_direct == DOUBLE_DIR)
	{
		ret = f_l_doubledir(cmd, STDOUT_FILENO);
		ret2 = dup2(fd_com1, STDIN_FILENO);
	}
	else if (cmd->f_direct == REDIR)
	{
		ret = f_l_redir(cmd, STDIN_FILENO);
		ret2 = dup2(fd_com2, STDOUT_FILENO);
	}
	else
	{
		ret = dup2(fd_com1, STDIN_FILENO);
		ret2 = dup2(fd_com2, STDOUT_FILENO);
	}
//	if (cmd->f_direct != NONE)
//		del_after_key(cmd->arg, cmd->f_direct);
	if (ret || ret2)
	{
		printf("%s: %s\n", cmd->arg->val, strerror(errno));
		return (1);
	}
	return (0);

//	dup2(fd[num_com - 1][0], STDIN_FILENO);
//	dup2(fd[num_com][1], STDOUT_FILENO);
}

