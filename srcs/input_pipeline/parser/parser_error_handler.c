/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 22:34:53 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/27 17:46:46 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	parser_error_handler(t_mini *mini)
{
	int	i;

	i = 0;
	while ((int)mini->lexer.op_lst[i].code != (int)mini->error_code)
		i++;
	ft_printf(SYNTAX_ERROR " '%s'\n", mini->lexer.op_lst[i].str);
	lexer_destroy(&mini->lexer);
	parser_destroy(mini->root);
	mini->error_code = SYNTAX;
}
