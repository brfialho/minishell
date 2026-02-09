/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:57:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/09 19:31:09 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_lexer(t_lexer *lexer, const char *input)
{
	char	*s;

	lexer->token_lst = safe_calloc(1, sizeof(t_list **));
	if (!lexer->token_lst)
		return ;
	init_operators(lexer);
	s = (char *)input;
	while (*s)
	{
		while (*s == ' ')
			s++;
		s = tokenize(lexer, s);
	}
}
