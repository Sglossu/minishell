//
// Created by Shasta Glossu on 11/19/21.
//

//t_list	*env = 0;
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("12345678")));
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("styshfj")));
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("PATH=jhkfk=kjgh")));
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("var2=var2=")));
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("var22=lkjkj")));
//
//ft_env(env);
//write(1, "\n", 1);
//
//t_list *arg = ft_lstnew(ft_strdup("unset"));
//
//ft_putendl_fd("\tcase Nothing", 1);
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("Nothing")));
//ft_unset(&env, arg);
//ft_env(env);
//write(1, "\n", 1);
//
//
//ft_putendl_fd("\tcase var2", 1);
//arg = ft_lstnew(ft_strdup("unset"));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var2")));
//ft_unset(&env, arg);
//ft_env(env);
//write(1, "\n", 1);
//
//ft_putendl_fd("\tcase var2 var22", 1);
//arg = ft_lstnew(ft_strdup("unset"));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var2")));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var22")));
//ft_unset(&env, arg);
//ft_env(env);
//write(1, "\n", 1);
//
//
//ft_putendl_fd("\tcase ''", 1);
//arg = ft_lstnew(ft_strdup("unset"));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("")));
//ft_unset(&env, arg);
//ft_env(env);
//write(1, "\n", 1);
//
//ft_putendl_fd("\tcase 12345678 styshfj", 1);
//arg = ft_lstnew(ft_strdup("unset"));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("12345678")));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("styshfj")));
//ft_unset(&env, arg);
//ft_env(env);
//write(1, "\n", 1);
//
//ft_putendl_fd("\tcase PATH var2=", 1);
//arg = ft_lstnew(ft_strdup("unset"));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("PATH"))); // должна быть ошибка
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var2=")));
//ft_unset(&env, arg);
//ft_env(env);
//write(1, "\n", 1);
//
//ft_putendl_fd("\tcase '__'", 1);
//arg = ft_lstnew(ft_strdup("unset"));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("")));
//ft_unset(&env, arg);
//ft_env(env);
//write(1, "\n", 1);

#include "../includes/minishell.h"

int ft_unset(t_list **env, t_list *arg)
{
	t_list *tmp;

	arg = arg->next;
	while(arg)
	{
		tmp = ft_lstfind(*env, arg->val);
		if (tmp)
		{
			ft_lstremove(env, tmp);
		}
		arg = arg->next;
	}
	return (0);
}