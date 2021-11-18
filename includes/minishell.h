//
// Created by Shasta Glossu on 11/16/21.
//

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include "../libft/libft.h"


void	ft_pwd(void);
void	ft_cd(void);
int		ft_env(t_list *lst);
int 	ft_unset(t_list **env, t_list *arg);

#endif
