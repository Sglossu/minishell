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

	t_list	*arg;
	arg = ft_lstnew(ft_strdup("cd"));
	ft_lstadd_back(&arg, ft_lstnew(ft_strdup("../")));
	ft_lstadd_back(&arg, ft_lstnew(ft_strdup("styshfj")));


	ft_cd(&all->env, arg);
	ft_pwd();
	ft_env(all->env);

	return 0;
}
