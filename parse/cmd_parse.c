/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:15:22 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/31 20:03:34 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_cmd_struct(t_all *all, t_list *HEAD)
{
	int		i;
	t_list	*tmp;

	i = 0;
	free_path(all);
	while (i < all->number_command)
	{
		free_path(all);
		all->cmd[i]->arg = copy_part_of_list(all, HEAD, i);
		tmp = all->cmd[i]->arg;
		if (is_dir(tmp->val))
		{
			dir_parse(all->cmd[i]);
			tmp = tmp->next;
			if (!all->cmd[i]->name_file)
			{
				ft_putendl_fd(": syntax error near unexpected token `newline'",
					STDERR_FILENO);
				return (1);
			}
			else
				tmp = tmp->next;
		}
		if (tmp && is_buildin(tmp->val))
		{
			all->cmd[i]->path_command = NULL;
			all->cmd[i]->type = BUILDIN;
			all->cmd[i]->flag_redirect = false;
			all->cmd[i]->status = 0;
			dir_parse(all->cmd[i]);
		}
		else if (tmp && is_binary(tmp->val, all))
		{
			all->cmd[i]->type = BINARY;
			all->cmd[i]->status = 0;
			all->cmd[i]->flag_redirect = false;
			all->cmd[i]->path_command = path_com(all, tmp->val);
			if (!all->cmd[i]->path_command)
				return (error_return_int());
			dir_parse(all->cmd[i]);
			free_path(all);
		}
		i++;
	}
	return (0);
}

int	num_of_commands(t_all *all, t_list *HEAD)
{
	int		res;
	t_list	*tmp;
	// int		pipes;
	int		num;
	int		flag;

	res = 0;
	num = 1;
	flag = 0;
	// pipes = 1;
	tmp = HEAD;
	while (tmp)
	{
		if (tmp->flag == COMMAND || tmp->flag == WTF)
			res++;
		if (num == 1 && tmp->flag == WTF)
		{
			ft_printf(STDERR_FILENO,"minishell: %s: command not found\n", tmp->val);
			g_status = 127;
		}
		// if ((is_buildin(tmp->val) || is_binary(tmp->val, all)) && pipes)
		// {
		// 	res++;
		// 	pipes = 0;
		// }
		// else if (num == 1 && (!is_dir(tmp->val)))
		// {
		// 	ft_printf(STDERR_FILENO,
		// 		"minishell: %s: command not found\n", tmp->val);
		// 	g_status = 127;
		// 	flag = 1;
		// }
		if (!ft_strcmp(tmp->val, "|") && tmp->flag == PIPE)
		{
			// pipes = 1;
			num = 0;
		}
		// free_path(all);
		tmp = tmp->next;
		num++;
	}
	all->number_command = res;
	return (flag);
}

int	init_cmd_struct(t_all *all)
{
	int		i;

	i = 0;
	all->cmd = malloc(sizeof(t_cmd *) * (all->number_command + 1));
	while (i < all->number_command)
	{
		all->cmd[i] = malloc(sizeof(t_cmd));
		all->cmd[i]->arg = NULL;
		all->cmd[i]->path_command = NULL;
		all->cmd[i]->name_file = NULL;
		all->cmd[i]->f_direct = 0;
		i++;
	}
	all->cmd[i] = NULL;
	return (0);
}

int	dir_parse(t_cmd *cmd)
{
	t_list		*tmp;

	tmp = cmd->arg;
	while (tmp)
	{
		if (!ft_strcmp(tmp->val, ">"))
		{
			cmd->f_direct = DIR;
			if (tmp->next)
				cmd->name_file = ft_strdup(tmp->next->val);
			if (!cmd->name_file)
				return (error_return_int());
			return (0);
		}
		else if (!ft_strcmp(tmp->val, ">>"))
		{
			cmd->f_direct = DOUB_DIR;
			if (tmp->next)
				cmd->name_file = ft_strdup(tmp->next->val);
			if (!cmd->name_file)
				return (error_return_int());
			return (0);
		}
		else if (!ft_strcmp(tmp->val, "<"))
		{
			cmd->f_direct = REDIR;
			if (tmp->next)
				cmd->name_file = ft_strdup(tmp->next->val);
			if (!cmd->name_file)
				return (error_return_int());
			return (0);
		}
		else if (!ft_strcmp(tmp->val, "<<"))
		{
			cmd->f_direct = DOUB_REDIR;
			if (tmp->next)
				cmd->name_file = ft_strdup(tmp->next->val);
			if (!cmd->name_file)
				return (error_return_int());
			return (0);
		}
		else
		{
			cmd->f_direct = NONE;
			cmd->name_file = NULL;
		}
		tmp = tmp->next;
	}
	return (1);
}
