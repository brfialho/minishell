/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:57:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 14:35:22 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	init_operators(t_lexer *lexer);

void	ft_lexer(t_lexer *lexer, const char *input)
{
	char	*s;

	lexer->token_lst = safe_calloc(1, sizeof(t_list **));
	init_operators(lexer);
	s = (char *)input;
	while (*s)
	{
		while (*s == ' ')
			s++;
		s = tokenize(lexer, s);
	}
}

static void	init_operators(t_lexer *lexer)
{
	lexer->op_lst[0] = (t_operator){0, "<<", 2, HEREDOC};
	lexer->op_lst[1] = (t_operator){0, ">>", 2, APPEND};
	lexer->op_lst[2] = (t_operator){2, "&&", 2, LOGICAL_AND};
	lexer->op_lst[3] = (t_operator){2, "||", 2, LOGICAL_OR};
	lexer->op_lst[4] = (t_operator){0, "<", 1, INFILE};
	lexer->op_lst[5] = (t_operator){0, ">", 1, OUTFILE};
	lexer->op_lst[6] = (t_operator){0, "&", 1, INVALID};
	lexer->op_lst[7] = (t_operator){1, "|", 1, PIPE};
	lexer->op_lst[8] = (t_operator){0, ";", 1, INVALID};
	lexer->op_lst[9] = (t_operator){0, "=", 1, ASSIGNMENT};
	lexer->op_lst[10] = (t_operator){0, "(", 1, OPEN_PARENTHESIS};
	lexer->op_lst[11] = (t_operator){0, ")", 1, CLOSE_PARENTHESIS};
	lexer->op_lst[12] = (t_operator){0, "$", 1, EXPANSION};
}
