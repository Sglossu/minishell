//
// Created by Shasta Glossu on 11/19/21.
//

#include "../includes/minishell.h"

static char *split_for_dup(char *str, char c)
{
	while (*str != c)
		str++;
	str++;
	return (ft_strdup(str));
}

char **from_lst_to_buf(int argc, t_list *lst, char c)
{
	char 	**argv;
	int 	i;

	i = 0;
	argv = (char**)malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	argv[argc] = NULL;
	while(lst)
	{
		if (c == '=')
			argv[i] = split_for_dup(lst->val, c);
		else
			argv[i] = ft_strdup(lst->val);
		if (!argv[i])
		{
//			free всё что уже есть
			return (NULL);
		}
		i++;
		lst = lst->next;
	}
	return (argv);
}