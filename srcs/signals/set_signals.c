/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:13:50 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/07 03:02:48 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "set_signal.h"

void	sighandler(int sig)
{
	g_status_shell = sig;

	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals(void)
{
	signal(SIGINT, sighandler);
}

// void	set_heredoc_signals(void)
// {
// 	signal(SIGINT, sigint_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	sigint_handler(int sig)
// {
// 	g_status_shell = sig;
// }

// void	sigint_prompt(int sig)
// {
// 	(void)sig;
// 	g_status_shell = sig;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	sigint_heredoc(int sig)
// {
// 	(void)sig;
// 	g_status_shell = 130;
// 	write(1, "\n", 1);
// }
