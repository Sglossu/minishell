/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:08:57 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:09:02 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strisdigit(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1); // есть буква
		i++;
	}
	return (0); // нет буков, тока циферы
}

int	problems(char *str, int minus)
{
	int	len;

	len = ft_strlen(str);
	if (len == 20 && minus == -1)
	{
		if (str[len - 1] == '9')
			return (0);
		return (len);
	}
	else if (len == 19 && minus == 1)
	{
		if (str[len - 1] == '8' || str[len - 1] == '9')
			return (0);
		return (len);
	}
	else if ((len < 20 && minus == -1) || (len < 19 && minus == 1))
		return (len);
	else if ((len > 20 && minus == -1) || (len > 19 && minus == 1))
		return (0);
	return (0);
}

long long	ft_atoi_overflow(char *str)
{
	int			i;
	long long	minus;
	long long	nb;

	i = 0;
	minus = 1;
	nb = 0;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == ' ')
		i++;
	if ((str[i] == 45) || (str[i] == 43))
	{
		if (str[i++] == 45)
			minus = -1;
	}
	if (!problems(str, minus))
		return (0);
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			nb = nb * 10 + (str[i] - '0');
			i++;
		}
	}
	return (nb * minus);
}

int work_with_arg(char *str)
{
	long long	status_exit;

	if (!ft_atoi_overflow(str) && (ft_strcmp(str, "0") || ft_strcmp(str, "-0") || ft_strcmp(str, "+0")))
	{
		// overflow
		printf("exit: %s: numeric argument required\n", str);
		exit (255);
	}
	status_exit = ft_atoi_long(str);
	if (status_exit > 0) {
		return ((int)status_exit % 256);
	}
	else if (status_exit % 256 != 0)
		return ((int)(status_exit % 256 + 256));
	return (0);
}

int	ft_exit(t_list *arg)
{
	arg = arg->next;
	if (!arg)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		s_status = 0;
		exit (s_status);
	}
	ft_putstr_fd("exit ", STDOUT_FILENO);
	ft_putendl_fd(arg->val, STDOUT_FILENO);
	if (ft_strisdigit(arg->val)) // return 1 - есть буква
	{
		printf("exit: %s: numeric argument required\n", arg->val);
		exit (255);
	}
	if (arg->next)
	{
		printf("exit: too many arguments\n");
		return (255);
	}
	exit (work_with_arg(arg->val));
}
