/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:17:31 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/09 16:31:52 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_SIGNAL_H
# define SHELL_SIGNAL_H

# include <signal.h>
# include "defines.h"

void	set_signals(void);
void	sighandler_heredoc(int sig);

#endif