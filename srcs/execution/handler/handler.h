/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:15:03 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/11 14:58:28 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H

# include "parsing/parsing.h"
# include "execution/execution.h"
# include "main.h"

void	sigint_prompt(int sig);
void	sigint_handler(int sig);
void	sigint_heredoc(int sig);

#endif