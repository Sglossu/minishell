/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:17:25 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:17:31 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "stdbool.h"

# define MINISHELL	"\033[32mMinishell$ \033[0m"

# define 	DIR			3
# define	REDIR		4
# define	DOUB_DIR	5
# define 	DOUB_REDIR	6
# define 	NONE		7

# define	TEXT		8
# define	PIPE		9
# define	COMMAND		10

# define	BUILDIN		0
# define	BINARY		1

typedef struct s_cmd {
	t_list		*arg;
	char		*path_command; // под это нет маллока, так как замолочится потом
	pid_t		pid;
	int			type;
	char		*name_file;
	t_list		*files;
	int			f_direct;
	bool		combo;
}				t_cmd;

typedef struct s_all {
	t_list		*env;
	t_list		*exp;
	char		**path; // под это нет маллока, так как замолочится потом
	t_cmd		**cmd;
	int			number_command; // количество команд
	int			i; // номер вызываемой команды
	char 		*pwd;
	char 		*oldpwd;
}				t_all;

typedef struct s_str {
	char *input;
	char *buf;
	int iter;
	int	quote;
	int	ecran;
	int	dub_quote;
	int	dollars;
}				t_str;

int	g_status;

void	path_print(t_all *all); // потом удалить

//buidins
int		ft_pwd(t_all *all);
int		ft_cd(t_all *all, t_list **env, t_list *exp, t_list *arg);
void	ft_env(t_list *lst);
void	ft_unset(t_list **env, t_list *exp, t_list *arg);
int		ft_export(t_all *all, t_list *arg);
void	new_copy_env(t_all *all);
char	*str_arg_in_quote(char *str);
int		ft_echo(t_list *arg);
int		ft_exit(t_list *arg);

//utils
char	**ft_sort_params(int argc, t_list *lst);
char	**from_lst_to_buf(int argc, t_list *lst, char c);
char	*find_after_equals(char *str);
char	*find_before_equals(char *str);
void	print_params(char **buf, int count);
int		str_is_variable(char *str);
char	*change_shlvl(char *str_old);
void	namefiles_in_arguments(t_cmd *cmd, t_list *lst);
void	print_lst(t_list *lst); // delete

//srcs
void	init(t_all *all, char **envi);
void	remember_pwd(t_all *all);

//pipe and redirect
int		our_pipe(t_all *all);
int		main_function_for_one_direct(t_all *all);
int		one_direct(t_all *all);
int		ft_doubleredir(t_cmd *cmd, int fd_std, int fd_0);
int		ft_redir(t_cmd *cmd, int fd_std);
int		ft_doubledir(t_cmd *cmd, int fd_std);
int		ft_dir(t_cmd *cmd, int fd_std);
int		pipe_for_two(t_all *all);

//main
int		main_work(t_all *all);
void	child(t_all *all, int all_i);
int		if_buildins(t_all *all, t_list *arg);

//parse
void	path_pl_command(t_all *all, char *command);
int		parse(t_all *all, char *input);
int		parse_path(t_all *all);
int		is_binary(char *val, t_all *all);
int		is_buildin(char *val);

//parse_utils

// {preparse}
char	*ft_quote(t_str *myString, char sym);
// char	*ft_dubquoute(char *input, int *i, t_all *all);
// char	*ft_dollar(char *input, t_all *all, int *i);

// {CMD}
void	num_of_commands(t_all *all, t_list *HEAD);
int		init_cmd_struct(t_all *all);
int		fill_cmd_struct(t_all *all, t_list *HEAD);
char	*path_com(t_all *all, char *command);
int		dir_parse(t_cmd *cmd);
void	combo_check(t_cmd *cmd);

// {LISTS}
t_list	*make_list_with_all_word(char *input);
t_list	*copy_part_of_list(t_all *all, t_list *HEAD, int num_command);
void	ft_lstprint(t_list *HEAD);

//free
int		ft_free(t_all *all);

//signal
void	ft_signal_in_child(void);
void	ft_signal_main(void);
void	ft_signal_run_pipes(void);
void	ft_signal_cltr_c_main(int sig);
void	ft_signal_pipes(int sig);
void	ft_signal_cltr_c_child(int sig);
void	ft_signal_quit_child(int sig);

#endif
