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

// SIGINT	Cntrl+C
// SIGTERM	Cntrl+
// SIGQUIT	Cntrl+backslash

void	ft_signal_quit_child(int sig)
{
	char	*quit;

	quit = ft_itoa(sig);
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putendl_fd(quit, STDERR_FILENO);
	free(quit);
	quit = NULL;
	s_status= 131;
}

void	ft_signal_cltr_c_child(int sig)
{
	(void)sig;
//	ft_putendl_fd("hui", STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	s_status = 130;
}

void	ft_signal_in_child(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, ft_signal_cltr_c_child);
	signal(SIGQUIT, ft_signal_quit_child);
}

void	ft_signal_main(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_cltr_c_main);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_run_pipes(void)
{
	signal(SIGINT, ft_signal_pipes);
	signal(SIGQUIT, ft_signal_pipes);
}

void	ft_signal_cltr_c_main(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	s_status = 130;
}

void	ft_signal_pipes(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void)sig;
}
