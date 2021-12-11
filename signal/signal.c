//
// Created by Shasta Glossu on 12/9/21.
//

#include "../includes/minishell.h"

void	ft_signal_in_child(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_signal_main(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_run_pipes(void)
{
	signal(SIGINT, ft_signal_pipes);
	signal(SIGQUIT, ft_signal_pipes);
}

void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
//	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	s_status = 130;
}

void	ft_signal_pipes(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void)sig;
}