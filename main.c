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

<<<<<<< HEAD
		all->cmd[0]->f_direct = REDIR;
		all->cmd[0]->name_file = "1";
		if_command_exist(all);
=======
		if_command_exist(all);
		all->cmd[all->i]->f_direct = DIR;
		all->cmd[all->i]->name_file = ft_strdup("2");
>>>>>>> 973fa81f5b1b4ed802e81d0bcbe10ff5ba864eb5

		if (all->number_command == 1 && all->cmd[0]->f_direct == NONE)
			main_work(all); // основная функция работы
		else if (all->number_command == 1 && all->cmd[0]->f_direct != NONE)
<<<<<<< HEAD
			one_direct(all);
=======
			one_with_direct(all);
>>>>>>> 973fa81f5b1b4ed802e81d0bcbe10ff5ba864eb5
		else
			our_pipe(all);
        free(input);
	}

	return 0;
}
