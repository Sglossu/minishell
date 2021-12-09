#include "../includes/minishell.h"

void	ft_lstprint(t_list *HEAD)
{
	t_list	*tmp;
	int		count;

	tmp = HEAD;
	count = 1;
	while (tmp)
	{
		printf("|%s| - arg %d\n", tmp->val, count);
		count++;
		tmp = tmp->next;
	}
}

void	make_list(char *input, t_list *tmp)
{
	int	i;

	i = 0;
	if (input[i] == '|')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup("|")));
	else if (input[i] == '>' && input[i+1] == '>')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(">>")));
	else if (input[i] == '<' && input[i+1] == '<')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup("<<")));
	else if (input[i] == '>')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(">")));
	else if (input[i] == '<')
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup("<")));
}

t_list	*make_list_with_all_word(char *input)
{
	int		i;
	int		j;
	t_list	*tmp;
	char	*str;

	i = 0;
	tmp = NULL;
	while(input[i])
	{
		if (input[i] != ' ')
		{
			j = i;
			while (input[j] && input[j] != ' ' && input[j] != '|'
					 && input[j] != '<' && input[j] != '>' )
				j++;
			str = ft_substr(input, i, j - i);
			if (ft_strlen(str) > 0)
				ft_lstadd_back(&tmp, ft_lstnew(str));
			else
				free(str);
			i = j;
			make_list(input + j, tmp);
		}
		i++;
	}

	return(tmp);
}

t_list	*copy_part_of_list(t_all *all, t_list *HEAD, int num_command)
{
	t_list	*tmp;
	t_list	*res;
	tmp = HEAD;
	res = NULL;

	(void) all;

	while (num_command)
	{
		if (!ft_strcmp(tmp->val, "|"))
			num_command--;
		tmp = tmp->next;
	}
	while (tmp && ft_strcmp(tmp->val, "|"))
	{
		ft_lstadd_back(&res, ft_lstnew(ft_strdup(tmp->val)));
		tmp = tmp->next;
	}
	return(res);
}