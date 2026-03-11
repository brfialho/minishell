/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:13:50 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/10 23:29:52 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "shell_signal.h"

static void	sighandler(int sig);

void	set_signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

static void	sighandler(int sig)
{
	g_shell_signal = sig;
}

int	shell_signal_hook(void)
{
	if (g_shell_signal == SIGINT)
	{
		rl_done = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (0);
}
