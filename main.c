/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:31:56 by bshawn            #+#    #+#             */
/*   Updated: 2021/11/25 20:11:42 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"

int	main(int argc, char **argv, char **envi)
{
	(void)argc;
	(void)argv;

	t_all	*all;
	char	*input;

	all = malloc(sizeof(t_all));
	if (!all)
		return (1); //error
	init(all, envi);
	while (1)
	{
		input = readline("Minishell☺% ");
		if (!input)
			exit(1);
		rl_bind_key('\t', rl_complete);
        add_history(input);
		parse(all, input);

		all->cmd[0]->f_direct = DOUB_REDIR;
		all->cmd[0]->name_file = "1";
		if_command_exist(all);

		int fd[2];
		pipe(fd);

		if (all->number_command == 1 && all->cmd[0]->f_direct == NONE)
			main_work(all); // основная функция работы
//		else if (all->number_command == 1 && all->cmd[0]->f_direct != NONE)
//			one_direct(all);
		else if (all->number_command == 1 && all->cmd[0]->f_direct != NONE)
		{
			ft_doubleredir(all->cmd[0], STDIN_FILENO, fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (if_buildins(&all->env, all->cmd[0]->arg))
				child(all, 0);
		}
		else
			our_pipe(all);
        free(input);
	}

	return 0;
}
