#include "includes/minishell.h"

int main(int argc, char **argv, char **envi)
{
	(void)argc;
	(void)argv;
	(void)envi;

	t_list	*env = 0;
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("PATH=jhkfk=kjgh")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("sss=dddd")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("pupu=12345678")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("PWD=var2=var2=")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("var22=lkjkj")));

	t_list *arg = ft_lstnew(ft_strdup("unset"));
	ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var2")));
	ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var22")));

	ft_export(&env, arg);

	return 0;
}
