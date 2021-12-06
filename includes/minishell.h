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
# include <sys/errno.h>
# include "sys/wait.h"
# include <errno.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "stdbool.h"

<<<<<<< HEAD
# define 	DIR			3
# define	REDIR		4
# define	DOUB_DIR	5
# define 	DOUB_REDIR	6
# define 	NONE		7
=======
# define DIR			3 // >
# define REDIR			4 // <
# define DOUBLE_DIR		5 // >>
# define DOUBLE_REDIR	6 // <<
# define NONE			0 // нет перенаправления
>>>>>>> 973fa81f5b1b4ed802e81d0bcbe10ff5ba864eb5

typedef struct s_cmd {
	t_list		*arg;
	char 		*path_command; // под это нет маллока, так как замолочится потом
	pid_t		pid;
<<<<<<< HEAD
	char 		*name_file;
	int 		f_direct;
=======
	int 		f_direct;
	char 		*name_file; // for redirect
>>>>>>> 973fa81f5b1b4ed802e81d0bcbe10ff5ba864eb5
}				t_cmd;

typedef struct s_all {
	t_list		*env;
	char 		**path; // под это нет маллока, так как замолочится потом
	t_cmd		**cmd;
	int 		number_command; // количество команд
	int 		i; // номер вызываемой команды
}				t_all;

//buidins
void	ft_pwd(void);
int		ft_cd(t_list **env, t_list *arg);
int		ft_env(t_list *lst);
int 	ft_unset(t_list **env, t_list *arg);
int		ft_export(t_list **env, t_list *arg);
int		ft_echo(t_list *arg);
int		ft_exit(t_list *arg);

//utils
char	**ft_sort_params(int argc, t_list *lst);
char	**from_lst_to_buf(int argc, t_list *lst, char c);
char	*find_after_equals(char *str);

//srcs_init
void	init(t_all *all, char **envi);

//pipe and redirect
int		our_pipe(t_all *all);
int		first_last_pipe(t_cmd *cmd, int fd, int fd_std);
int		middle_pipe(t_cmd *cmd, int fd_com1, int fd_com2);

int		f_l_dir(t_cmd *cmd, int fd);
int		f_l_doubledir(t_cmd *cmd, int fd);
int		f_l_redir(t_cmd *cmd, int fd);

//main
int		main_work(t_all *all);
int		if_command_exist(t_all *all);
void	child(t_all *all, int all_i);
<<<<<<< HEAD
int		one_direct(t_all *all);
int		if_buildins(t_list **env, t_list *arg);
=======
int		if_buildins(t_list **env, t_list *arg);
int		one_with_direct(t_all *all);
>>>>>>> 973fa81f5b1b4ed802e81d0bcbe10ff5ba864eb5

//parse
int		parse(t_all *all, char *input);




#endif
