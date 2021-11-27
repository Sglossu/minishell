//
// Created by Shasta Glossu on 11/16/21.
//

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <errno.h>
# include "../libft/libft.h"
# include "stdbool.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_all {
	t_list	*env;
	t_list	*arg;
	char	**path;
	pid_t	pid;
	char	*path_command;
}				t_all;

//buidins
void	ft_pwd(void);
int		ft_cd(t_list **env, t_list *arg);
int		ft_env(t_list *lst);
int		ft_unset(t_list **env, t_list *arg);
int		ft_export(t_list **env, t_list *arg);
int		ft_echo(t_list *arg);
int		ft_exit(t_list *arg);

//utils
char	**ft_sort_params(int argc, t_list *lst);
char	**from_lst_to_buf(int argc, t_list *lst, char c);
char	*find_after_equals(char *str);

//srcs_init
void	init(t_all **all, char **envi);

//main
int		main_work(t_all **all);
int		if_command_exist(t_all **all);

//parse
int		parse(t_all **all, char *input);

#endif
