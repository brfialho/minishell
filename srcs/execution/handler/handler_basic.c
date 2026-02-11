/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:28:56 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/11 14:54:59 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_status_shell = 130;
}

void	sigint_prompt(int sig)
{
	(void)sig;
	g_status_shell = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	g_status_shell = 130;
	write(1, "\n", 1);
}
