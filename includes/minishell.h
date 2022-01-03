/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:17:25 by sglossu           #+#    #+#             */
/*   Updated: 2022/01/04 00:31:45 by bshawn           ###   ########.fr       */
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

# define    DIR			3
# define    REDIR		4
# define    DOUB_DIR	5
# define    DOUB_REDIR	6
# define    NONE		7

# define    TEXT		8
# define    PIPE		9
# define    DIRECT		10
# define    COMMAND     11
# define    WTF         12

# define    BUILDIN		0
# define    BINARY		1

typedef struct s_cmd {
	t_list		*arg;
	char		*path_command;
	pid_t		pid;
	int			type;
	char		*name_file;
	int			f_direct;
	int			status;
	bool		flag_redirect;
	bool		flag_127;
}				t_cmd;

typedef struct s_all {
	t_list		*env;
	t_list		*exp;
	char		**path;
	t_cmd		**cmd;
	int			number_command;
	int			i;
	char		*pwd;
	char		*oldpwd;
	int			count_doub_redir;
}				t_all;

int	g_status;

//buidins
int		ft_pwd(t_all *all);
int		ft_cd(t_all *all, t_list *arg);
void	ft_env(t_list *arg, t_list *lst);
void	ft_unset(t_list **env, t_list *arg);
int		ft_export(t_all *all, t_list *arg);
void	new_copy_env(t_all *all);
char	*str_arg_in_quote(char *str);
int		ft_echo(t_list *arg);
int		ft_exit(t_list *arg);
char	*home(t_list **env);
int		utils_cd(t_all *all, char *str);

//utils
char	**ft_sort_params(int argc, t_list *lst);
char	**from_lst_to_buf(int argc, t_list *lst, char c);
char	*find_after_equals(char *str);
char	*find_before_equals(char *str);
void	print_params(char **buf, int count);
int		str_is_variable(char *str, t_list *tmp);
char	*change_shlvl(char *str_old);
void	error_return_nothing(void);
char	*error_return_null(void);
int		error_return_int(void);
void	free_buf(char **buf);

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
int		pipe_for_another(t_all *all, int com);
int		fork_and_close(t_all *all, int com, int **fd, int i);
int		what_is_direct(t_all *all);
void	how_much_doub_redir(t_all *all);
char	*direct_for_lstfind(t_cmd *cmd);
int		execute_and_delete_redir(t_all *all);
void	how_much_doub_redir(t_all *all);
void	if_doub_redir(t_cmd *cmd);
void	fd_close(int i, int **fd);

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
int		error_token(void);
int		is_dir_after_pipe(t_list *head);

// preparse
int		is_dir(char *str);
int		is_dollar(char *str);
int		is_ecran(char *str);
char	*ft_dollar(char *input, t_all *all, int *i);
char	*ready_string(t_list *tmp, t_all *all, int *flag, int i);
char	*loop_ready_string(t_all *all, char **str, int *flag, int i);

// cmd
int		num_of_commands(t_all *all, t_list *head);
int		init_cmd_struct(t_all *all);
int		fill_cmd_struct(t_all *all, t_list *head);
int		fill_cmd_struct_help(t_all *all, t_cmd *cmd, t_list *tmp);
char	*path_com(t_all *all, char *command);
int		dir_parse(t_cmd *cmd);
int		dir_parse_help(t_list *tmp, t_cmd *cmd, int dir_type);
int		is_wtf(t_all *all, t_list *tmp);

// lists
t_list	*make_list_with_all_word(char *input);
t_list	*copy_part_of_list(t_all *all, t_list *HEAD, int num_command);
char	*ft_ecran(char *input, int *i);

//free
int		ft_free(t_all *all);
void	free_path(t_all *all);
void	free_cmd(t_cmd *cmd);
void	free_fd(t_all *all, int **fd);

//signal
void	ft_signal_in_child(void);
void	ft_signal_main(void);
void	ft_signal_run_pipes(void);
void	ft_signal_cltr_c_main(int sig);
void	ft_signal_pipes(int sig);
void	ft_signal_cltr_c_child(int sig);
void	ft_signal_quit_child(int sig);

#endif
