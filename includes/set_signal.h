/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:17:31 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/05 20:35:37 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_SIGNAL_H
# define SET_SIGNAL_H

# include <signal.h>
# include "defines.h"


void	set_prompt_signals(void);
void	set_heredoc_signals(void);

#endif