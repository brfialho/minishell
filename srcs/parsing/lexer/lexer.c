/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:57:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/23 15:17:49 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	lexer(t_list **head, char *input)
{
	char	*s;
	t_token	*token_lst;

	s = input;
	while (*s)
	{
		token_lst = ft_calloc(1, sizeof(t_token));
		if (!token_lst)
			return ;
		token_lst->code = WORD;
		token_lst->string = ft_strdup(&s++[0]);
		lst_add_end(head, lst_new_node(token_lst));
	}
}