/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:31:37 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/14 03:36:07 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bool	process_input_pipeline(t_mini *mini)
{
	mini->root = NULL;
	mini->error_status = NO_ERROR;
	if (!ft_strcmp(mini->input, WHITESPACE))
		return (EXIT_FAILURE);
	mini->error_status = ft_lexer(&mini->lexer, mini->input);
	if (mini->error_status)
		return (lexer_error_handler(mini), EXIT_FAILURE);
	mini->error_status = parser(&mini->root, &mini->lexer);
	if (mini->error_status)
		return (parser_error_handler(mini), EXIT_FAILURE);
	lexer_destroy(&mini->lexer);
	mini->error_status = collect_heredocs(mini);
	if (mini->error_status)
		return (parser_destroy(mini->root), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
