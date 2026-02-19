/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:17:31 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 13:44:43 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_SIGNALS_H
# define SET_SIGNALS_H

# include "parsing.h"
# include "execution.h"
# include "main.h"

void	set_prompt_signals(void);
void	set_heredoc_signals(void);

#endif