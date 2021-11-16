//
// Created by Shasta Glossu on 11/16/21.
//

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;
	pwd = getcwd(NULL, 1024);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		printf("%s\n", strerror(errno));
	}
}