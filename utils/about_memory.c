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

void free_buf(char **buf)
{
	int i = 0;
	int j = 0;

	while (buf[i])
	{
		while(buf[j])
		{
			free(buf[j]);
			buf[j] = NULL;
			j++;
		}
		free(buf[i]);
		buf[i] = NULL;
		i++;
	}
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
			free_buf(argv);
			return (NULL);
		}
		i++;
		lst = lst->next;
	}
	return (argv);
}