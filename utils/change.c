#include "../includes/minishell.h"

void	change_after_equals_in_list(t_all *all, t_list tmp, char *str)
{
	char	*str1;
	char	*tmp_new;

	str1 = find_before_equals(str);
	tmp_new = ft_strjoin(str1, str); // новая строка
	free(str1);
	if (!tmp_new)
	{
		g_status = errno;
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	ft_lstremove(&all->env, &tmp);
	ft_lstadd_back(&all->env, ft_lstnew(tmp_new));
}