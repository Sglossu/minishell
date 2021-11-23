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


	all->arg = ft_lstnew(ft_strdup("exit"));
	ft_lstadd_back(&all->arg, ft_lstnew(ft_strdup("9")));
//	ft_lstadd_back(&arg, ft_lstnew(ft_strdup("styshfj")));
	while (1)
	{
		main_work(&all); // основная функция работы
		exit(0);
	}

	return 0;
}
