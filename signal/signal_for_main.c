/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:16:07 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:16:14 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_main(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_cltr_c_main);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_cltr_c_main(int sig)
{
	(void)sig;
	write(2, "\n", 1);
//	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}
