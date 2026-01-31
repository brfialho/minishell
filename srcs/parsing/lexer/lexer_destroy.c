/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:44:30 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/30 22:06:32 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	del_token(void	*content);

void	lexer_destroy(t_lexer *lexer)
{
	if (*lexer->token_lst)
		lst_del_all(lexer->token_lst, del_token);
	free(lexer->token_lst);
	lexer->token_lst = NULL;
}

static void	del_token(void	*content)
{
	t_token	*token;

	token = content;
	if (token->code == WORD)
		free(token->string);
	free(token);
}