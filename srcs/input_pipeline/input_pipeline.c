/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:22:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/09 18:08:09 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_error	collect_heredocs(t_mini *mini);

t_bool	process_input_pipeline(t_mini *mini)
{
	mini->error_code = NO_ERROR;
	if (!ft_strcmp(mini->input, WHITESPACE))
		return (EXIT_FAILURE);
	mini->error_code = ft_lexer(&mini->lexer, mini->input);
	if (mini->error_code)
		return (lexer_error_handler(mini), EXIT_FAILURE);
	mini->error_code = parser(&mini->root, &mini->lexer);
	if (mini->error_code)
		return (parser_error_handler(mini), EXIT_FAILURE);
	lexer_destroy(&mini->lexer);
	mini->error_code = collect_heredocs(mini);
	if (mini->error_code)
		return (parser_destroy(mini->root), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
