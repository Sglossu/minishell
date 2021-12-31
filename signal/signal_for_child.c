/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_for_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:46:41 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:46:43 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_quit_child(int sig)
{
	char	*quit;

	quit = ft_itoa(sig);
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putendl_fd(quit, STDERR_FILENO);
	free(quit);
	quit = NULL;
	g_status = 131;
}

void	ft_signal_cltr_c_child(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	g_status = 130;
}

void	ft_signal_in_child(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, ft_signal_cltr_c_child);
	signal(SIGQUIT, ft_signal_quit_child);
}

void	ft_signal_run_pipes(void)
{
	signal(SIGINT, ft_signal_pipes);
	signal(SIGQUIT, ft_signal_pipes);
}

void	ft_signal_pipes(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void)sig;
}
