/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:31:56 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/29 14:28:27 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void ft_bshawn_free(t_all *all, char *input)
{
	// t_list	*tmp;
	int		i;
	int		x;

	x = 0;
	i = 0;
	
	while (all->cmd[x])
	{
		ft_lstclear(&all->cmd[x]->arg, free);
		if (all->cmd[x]->path_command)
			free(all->cmd[x]->path_command);
		x++;
	}
	all->cmd = NULL;

	free(input);
}


void show_path(t_all *all)
{
	int	i=0;

	if (all->path)
	{
		while (all->path[i++])
			printf("|%s|>PATH\n", all->path[i]);
	}
}

int	main(int argc, char **argv, char **envi)
{
	t_all	*all;
	char	*input;

	(void)argc;
	(void)argv;
	g_status = 0;
	all = malloc(sizeof(t_all));
	rl_outstream = stderr;
	if (!all)
		return (1);
	init(all, envi);
	while (1)
	{
		ft_signal_main();
		input = readline(MINISHELL);
		if (!input)
		{
			//			 ft_putendl_fd("exit\n", 2);
			exit(g_status);
			//			input = ft_strdup("exit");
		}

		rl_bind_key('\t', rl_complete);
		if (!ft_strcmp(input, ""))
			continue;
		add_history(input);
		parse(all, input);
		if (all->number_command == 1 && all->cmd[0]->f_direct == NONE)
			main_work(all);
		else if (all->number_command == 1 && all->cmd[0]->f_direct != NONE)
			one_direct(all);
		else if (all->number_command > 1)
			our_pipe(all);
		 free(input);
		 ft_free(all);
	}
	return (g_status);
}
