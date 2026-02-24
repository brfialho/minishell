/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:22:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 02:20:25 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bool	parsing(t_mini *mini)
{
	if (ft_lexer(&mini->lexer, mini->input))
		return (EXIT_FAILURE);
	trim_quoted_tokens(&mini->lexer);
	parser(&mini->root, &mini->lexer);
	return (EXIT_SUCCESS);
}
