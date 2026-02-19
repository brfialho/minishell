/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:15:03 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 14:50:34 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H

void	sigint_prompt(int sig);
void	sigint_handler(int sig);
void	sigint_heredoc(int sig);

#endif