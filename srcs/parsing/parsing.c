/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:22:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 18:30:57 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	parsing(t_mini *mini)
{
	ft_lexer(&mini->lexer, mini->input);
	mini->root = parser(&mini->lexer);
}
