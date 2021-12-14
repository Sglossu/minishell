//
// Created by Shasta Glossu on 11/16/21.
//

#include "../includes/minishell.h"

char	*home(t_list **env)
{
	t_list	*tmp;
	char 	*str;

	tmp = ft_lstfind((*env), "HOME");
	if (!tmp)
	{
		ft_putendl_fd("cd: HOME not set", STDOUT_FILENO);
		s_status = 1;
	}
	else
	{
		str = find_after_equals(tmp->val);
		if (!str) // нет =
		{
			ft_putendl_fd("cd: HOME not set", STDOUT_FILENO);
			s_status = 1;
		}
		else
			return (str);
	}
	return (NULL);
}

int	change_pwd_oldpwd(t_list **env, char **oldpwd)
{
	char	*pwd;
	t_list	*tmp;

	pwd = getcwd(NULL, 1024);
	tmp = ft_lstfind(*env, "PWD");
	if (!tmp)
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("PWD=", pwd)));
	else
		tmp->val = ft_strjoin("PWD=", pwd);

	tmp = ft_lstfind(*env, "OLDPWD");
	if (!tmp)
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("OLDPWD=", *oldpwd)));
	else
		tmp->val = ft_strjoin("OLDPWD=", *oldpwd);
	return (0);
}

void	ft_cd(t_list **env, t_list *arg)
{
	(void)env;
	char 	*str;
	char 	*oldpwd;

	if (!arg->next || !ft_strcmp(arg->next->val, "~"))
		str = home(env);
	else
		str = ft_strdup(arg->next->val);
	if (!str)
		return; // error - уже напечатана
	oldpwd = getcwd(NULL, 1024);
	if (chdir(str) == -1 && str)
	{
		s_status = errno;
		printf("%s: %s: %s\n", arg->val, str, strerror(errno));
	}
	else
		change_pwd_oldpwd(env, &oldpwd);
}