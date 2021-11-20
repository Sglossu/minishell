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

//buidins
void	ft_pwd(void);
void	ft_cd(void);
int		ft_env(t_list *lst);
int 	ft_unset(t_list **env, t_list *arg);
int		ft_export(t_list **env, t_list *arg);
int		ft_echo(t_list *arg);

//utils
char	**ft_sort_params(int argc, t_list *lst);
char	**from_lst_to_buf(int argc, t_list *lst, char c);



#endif
