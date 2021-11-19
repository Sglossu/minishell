//
// Created by Shasta Glossu on 11/19/21.
//

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
	(void)arg;
	char 	**buf;
	int 	count;
	t_list	*exp = 0;
	t_list	*tmp;

	tmp = *env;
	while(tmp)
	{
		ft_lstadd_back(&exp, tmp);
		printf("%s\n", exp->val);
		tmp = tmp->next;
		write(1, "1\n", 2);
	}
	write(1, "2\n", 2);
//	while (arg)
//	{
//
//	}

	count = count_params(exp);
    buf = ft_sort_params(count, exp);
    if (!buf)
    	return (1); // error
    print_params(buf, count);
    return (1);
}