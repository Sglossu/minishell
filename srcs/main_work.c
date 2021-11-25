//
// Created by Shasta Glossu on 11/24/21.
//

#include "../includes/minishell.h"

int if_buildins(t_list **env, t_list *arg)
{
	if (!ft_strcmp(arg->val, "cd"))
		ft_cd(env, arg);
	else if (!ft_strcmp(arg->val, "echo"))
		ft_echo(arg);
	else if (!ft_strcmp(arg->val, "env"))
		ft_env(*env);
	else if (!ft_strcmp(arg->val, "exit"))
		ft_exit(arg);
	else if (!ft_strcmp(arg->val, "export"))
		ft_export(env, arg);
	else if (!ft_strcmp(arg->val, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(arg->val, "unset"))
		ft_unset(env, arg);
	else
		return (1); // совпадений нет
	return (0); // запустился билдин
}

void	child(t_all **all)
{
	char	**arg;
	char	**env;
	int 	i = 0;

	arg = from_lst_to_buf(ft_lstsize((*all)->arg), (*all)->arg, '\0');
	env = from_lst_to_buf(ft_lstsize((*all)->env), (*all)->env, '\0');
	execve((*all)->path_command, arg, env);
	while (arg[i])
	{
		free(arg[i]);
		arg[i] = NULL;
		i++;
	}
	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	exit(0);
}

int	main_work(t_all **all)
{
	int status;

	if (!if_buildins(&(*all)->env, (*all)->arg))
		return (0); // то есть есть такой билдин
	else
	{
		if (!if_command_exist(all))
		{
			(*all)->pid = fork();
			if ((*all)->pid == 0)
			{
				child(all);
			}
			else
				waitpid((*all)->pid, &status, 0);
		}
	}
	return (1);
}
