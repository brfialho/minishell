/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:13:50 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/09 17:02:41 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "shell_signal.h"

static int shell_signal_hook(void);
static void	sighandler(int sig);

void	sighandler_heredoc(int sig)
{
	g_status_shell = sig;

	if (sig == SIGINT)
		rl_done = 1;
}

void	set_signals(void)
{
	rl_event_hook = shell_signal_hook;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

static void	sighandler(int sig)
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

static int shell_signal_hook(void)
{
	return (0);
}