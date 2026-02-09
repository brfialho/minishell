/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:33:53 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/09 19:31:29 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_operators(t_lexer *lexer)
{
	lexer->op_lst[0] = (t_operator){"<<", 2, HEREDOC};
	lexer->op_lst[1] = (t_operator){">>", 2, APPEND};
	lexer->op_lst[2] = (t_operator){"&&", 2, LOGICAL_AND};
	lexer->op_lst[3] = (t_operator){"||", 2, LOGICAL_OR};
	lexer->op_lst[4] = (t_operator){"<", 1, INFILE};
	lexer->op_lst[5] = (t_operator){">", 1, OUTFILE};
	lexer->op_lst[6] = (t_operator){"&", 1, INVALID};
	lexer->op_lst[7] = (t_operator){"|", 1, PIPE};
	lexer->op_lst[8] = (t_operator){";", 1, INVALID};
	lexer->op_lst[9] = (t_operator){"=", 1, ASSIGNMENT};
	lexer->op_lst[10] = (t_operator){"(", 1, OPEN_PARENTHESIS};
	lexer->op_lst[11] = (t_operator){")", 1, CLOSE_PARENTHESIS};
	lexer->op_lst[12] = (t_operator){"$", 1, EXPANSION};
}

t_token	*alloc_token(t_token_code code, char *s)
{
	t_token	*token;

	token = safe_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->code = code;
	token->string = s;
	return (token);
}
