//
// Created by Shasta Glossu on 11/18/21.
//

//char **buf;
//
//buf = (char **)ft_calloc(7, sizeof(char *));
//buf[0] = "echo";
//buf[1] = "p";
//buf[2] = "/Users/sglossu/.oh-my-zsh";
//buf[3] = "/usr/bin/env";
//buf[4] = "1";
//buf[5] = "hello";
//buf[6] = NULL;

#include "../includes/minishell.h"

void ft_echo(char **buf) // переделать
{
	int i;
	int line_break;

//	buf[0] = "echo"
	i = 1;
	line_break = 1;
	if (!ft_strcmp(buf[i], "-n"))
	{
		line_break = 0;
		i++;
	}
	while (buf[i])
	{
		ft_putstr_fd(buf[i], STDOUT_FILENO);
		if (line_break)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		else
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
}