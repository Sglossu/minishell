//
// Created by Shasta Glossu on 11/19/21.
//

//t_list	*env = 0;
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("PATH=aaa")));
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("sss=dddd")));
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("pupu=12345678")));
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("PWD=var2=var2=")));
//ft_lstadd_back(&env, ft_lstnew(ft_strdup("var22=bbb")));
//
//t_list *arg = ft_lstnew(ft_strdup("export"));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var2")));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var22=bbb")));
//
//ft_export(&env, NULL);


#include "../includes/minishell.h"

static int	count_params(t_list *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count += 1;
		env = env->next;
	}
	return (count);
}

static void print_params(char **buf, int count)
{
	int 	i;
	int 	j;

	j = 0;
	while (j < count)
	{
		i = 0;
		write(STDOUT_FILENO, "declare -x ", 11);
		while (buf[j][i] != 0)
		{
			write(1, &buf[j][i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
}

int ft_export(t_list **env, t_list *arg)
{
	char 	**buf;
	int 	count;
	t_list	*exp = 0;
	t_list	*tmp;

	tmp = *env;
	while(tmp)
	{
		ft_lstadd_back(&exp, ft_lstnew(tmp->val));
		tmp = tmp->next;
	}
	if (arg)
		arg = arg->next;
	tmp = arg;

	while (arg)
	{
		if(!ft_lstfind(exp, arg->val)) {
			ft_lstadd_back(&exp, ft_lstnew(arg->val));
		}
		arg = arg->next;
	}
	if (!tmp)
	{
		count = count_params(exp);
		buf = ft_sort_params(count, exp);
		if (!buf)
			return (1); // error
		print_params(buf, count);
	}
    return (1);
}