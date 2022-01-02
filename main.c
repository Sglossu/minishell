/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:31:56 by bshawn            #+#    #+#             */
/*   Updated: 2022/01/02 15:26:28 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static	int	minus_znaki(t_all *all)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	if (!all->cmd)
		return (0);
	tmp = all->cmd[i];
	while (tmp)
	{
		if ((!ft_strcmp(tmp->arg->val, ">") && !tmp->arg->next)
			|| (!ft_strcmp(tmp->arg->val, "<") && !tmp->arg->next)
			|| (!ft_strcmp(tmp->arg->val, ">>") && !tmp->arg->next)
			|| (!ft_strcmp(tmp->arg->val, "<<") && !tmp->arg->next))
		{
			g_status = 2;
			return (g_status);
		}
		i++;
		tmp = all->cmd[i];
	}
	return (0);
}

int	loop_main(t_all *all, char *input)
{
	if (!parse(all, input))
	{
		free_path(all);
		if(minus_znaki(all))
			return (1);
		if (!all->cmd)
			return (g_status);
		if (all->number_command == 1 && all->cmd[0]->f_direct == NONE)
			main_work(all);
		else if (all->number_command == 1 && all->cmd[0]->f_direct != NONE)
			one_direct(all);
		else if (all->number_command > 1)
			our_pipe(all);
		ft_free(all);
	}
	return (0);
}

int	main(int argc, char **argv, char **envi)
{
	t_all	*all;
	char	*input;

	(void)argc;
	(void)argv;
	g_status = 0;
	all = malloc(sizeof(t_all));
	if (!all)
		return (error_return_int());
	rl_outstream = stderr;
	init(all, envi);
	while (1)
	{
		ft_signal_main();
		input = readline(MINISHELL);
		if (!input)
			exit(g_status);
		rl_bind_key('\t', rl_complete);
		if (!ft_strcmp(input, ""))
			continue ;
		add_history(input);
		if (loop_main(all, input))
			continue;
		free(input);
	}
	return (g_status);
}
