/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:31:56 by bshawn            #+#    #+#             */
/*   Updated: 2021/11/29 19:48:57 by bshawn           ###   ########.fr       */
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

		printf("\n<<<<<parse start>>>>>\n\n");
		parse(all, input);
		printf("\n<<<<<parse complete>>>>>\n");

		printf("\n<<<<<main start>>>>>\n\n");
		if (all->number_command == 1)
			main_work(all); // основная функция работы
		// else if (all->number_command > 1)
		// 	our_pipe(all);
		printf("\n<<<<<main complete>>>>>\n\n");

		printf("\n<<<<<free structs start>>>>>\n\n");
		free(input);
		ft_free(all);
		printf("\n<<<<<free structs complete>>>>>\n\n");
	}

	return 0;
}
