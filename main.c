#include "includes/minishell.h"

int main(int argc, char **argv, char **envi)
{
	(void)argc;
	(void)argv;

	t_all	*all;

	all = malloc(sizeof(t_all));
	if (!all)
		return (1); //error
	init(&all, envi);

	all->number_of_pipes = 0; // количество частей, разделенных пайпами

	all->arg = ft_lstnew(ft_strdup("ls"));
//	ft_lstadd_back(&all->arg, ft_lstnew(ft_strdup("wc")));
//	ft_lstadd_back(&arg, ft_lstnew(ft_strdup("styshfj")));

	while (1)
	{
		if (all->number_of_pipes == 0)
			main_work(&all); // основная функция работы
		else if (all->number_of_pipes == 1)
			our_pipe(&all);
		exit(0);
	}

	return 0;
}
