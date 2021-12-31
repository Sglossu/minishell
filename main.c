/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:31:56 by bshawn            #+#    #+#             */
/*   Updated: 2021/12/31 18:59:17 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
			// ft_putendl_fd("exit\n", 2);
			exit(g_status);
			// input = ft_strdup("exit");
		}
		rl_bind_key('\t', rl_complete);
		if (!ft_strcmp(input, ""))
			continue ;
		add_history(input);
		if (!parse(all, input))
		{
			if (all->number_command == 1 && all->cmd[0]->f_direct == NONE)
				main_work(all);
			else if (all->number_command == 1 && all->cmd[0]->f_direct != NONE)
				one_direct(all);
			else if (all->number_command > 1)
				our_pipe(all);
			ft_free(all);
		}
		free(input);
	}
	return (g_status);
}
