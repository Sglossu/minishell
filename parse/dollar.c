/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:25:50 by bshawn            #+#    #+#             */
/*   Updated: 2022/01/01 19:41:54 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_name(char *input, int i)
{
	char	*name;
	int		j;

	name = NULL;
	j = i + 1;
	if (input[j] == '?' || ft_isdigit(input[j]))
	{
		j++;
	}
	else
	{
		while (input[j] && ft_isalnum(input[j]))
		{
			j++;
		}
	}
	name = ft_substr(input, i + 1, j - i - 1);
	if (!name)
		return (error_return_null());
	return (name);
}

char	*get_var_from_path(t_all *all, char *name)
{
	t_list	*env_obj;
	char	*res;

	if (!name)
		return (NULL);
	env_obj = ft_lstfind(all->env, name);
	if (env_obj)
		res = find_after_equals(env_obj->val);
	else
	{
		res = ft_strdup("");
		if (!res)
			return (error_return_null());
	}
	return (res);
}

char	*join_parts(char *input, char *change, char *name, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*res;
	int		j;

	if (!name)
		return (NULL);
	j = i + 1;
	j += ft_strlen(name);
	tmp = ft_substr(input, 0, i);
	if (!tmp)
		return (error_return_null());
	tmp2 = ft_strdup(input + j);
	if (!tmp2)
		return (error_return_null());
	tmp = ft_strjoin_gnl(tmp, change);
	if (!tmp)
		return (error_return_null());
	res = ft_strjoin(tmp, tmp2);
	if (!res)
		return (error_return_null());
	free (tmp);
	free (tmp2);
	return (res);
}

int	ft_len(char *name, char *change)
{
	int	res;
	int	len_name;
	int	len_change;

	if (!name)
		return (0);
	len_name = (int)ft_strlen(name);
	len_change = (int)ft_strlen(change);
	res = 0;
	if (!ft_strcmp(change, ""))
	{
		res = -1;
		return (res);
	}
	if (len_name > len_change)
	{
		res = len_name - len_change;
	}
	else if (len_change > len_name)
	{
		res = len_change - len_name;
	}
	return (res);
}

char	*ft_dollar(char *input, t_all *all, int *i)
{	
	char	*res;
	char	*name;
	char	*change;
	int		len;

	name = get_name(input, *i);
//	if (!name)
//		return (NULL);
	if (name && !ft_strcmp(name, "?"))
	{
		change = ft_itoa(g_status);
		if (!change)
			return (error_return_null());
	}
	else
		change = get_var_from_path(all, name);
	res = join_parts(input, change, name, *i);
	len = ft_len(name, change);
	*i += len;
	if (name)
		free(name);
	if (input)
		free(input);
	if (change)
		free(change);
	return (res);
}
