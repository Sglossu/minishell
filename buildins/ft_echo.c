//
// Created by Shasta Glossu on 11/18/21.
//

//t_list *arg = ft_lstnew(ft_strdup("echo"));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("-n")));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var2")));
//ft_lstadd_back(&arg, ft_lstnew(ft_strdup("var22=bbb")));
//
//ft_echo(arg);

#include "../includes/minishell.h"

int ft_echo(t_list *arg)
{
	int line_break;

	line_break = 1;
	arg = arg->next;
	if (arg && !ft_strcmp(arg->val, "-n"))
	{
		arg = arg->next;
		line_break = 0;
	}
	while (arg)
	{
		if (!ft_strcmp((arg->val), "$?"))
			ft_putnbr_fd(s_status, STDOUT_FILENO);
		else
			ft_putstr_fd(arg->val, STDOUT_FILENO);
		if (arg->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		arg = arg->next;
	}
	if (line_break)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}