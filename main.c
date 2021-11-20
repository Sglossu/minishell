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


	return 0;
}
