#include "../includes/minishell.h"

char	*str_arg_in_quote(char *str)
{
	char	*str1;
	char 	*str2;
	char 	*tmp;

	ft_printf(1, "str_old: %s\n", str);
	tmp = find_before_equals(str);
	ft_printf(1, "tmp1: %s\n", tmp);
	if (!tmp)
		return (ft_strdup(str));
	str1 = ft_strjoin(tmp, "\"");
	ft_printf(1, "str1: %s\n", str1);
	free(tmp);
	tmp = NULL;
	tmp = find_after_equals(str);
	str2 = ft_strjoin(tmp, "\"");
	ft_printf(1, "str2: %s\n", str2);
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin(str1, str2);
	ft_printf(1, "tmp2: %s\n", tmp);
	if (!tmp)
//		error
		return NULL;
	free(str1);
	free(str2);
	str1 = NULL;
	str2 = NULL;
	return (tmp);
}

void	new_copy_env(t_all *all)
{
	t_list	*tmp;
	char 	*tmp_str;

	if (all->exp)
		ft_lstclear(&all->exp, free);
	all->exp = NULL;
	tmp = all->env;
	while (tmp)
	{
		tmp_str = str_arg_in_quote(tmp->val);
		ft_lstadd_back(&all->exp, ft_lstnew(ft_strdup(tmp_str)));
		free(tmp_str);
		tmp_str = NULL;
//		ft_lstadd_back(&all->exp, ft_lstnew(tmp->val));
		tmp = tmp->next;
	}
//	tmp = all->exp;
//	while (tmp)
//	{
//		ft_putendl_fd(tmp->val, STDOUT_FILENO);
//		tmp = tmp->next;
//	}
}
