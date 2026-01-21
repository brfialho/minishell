/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:57:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/21 19:26:19 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tokenizer(t_list **head, char *input)
{
	char	*s;
	t_token	*token;

	s = input;
	while (*s)
	{
		token = ft_calloc(1, sizeof(t_token));
		if (!token)
			return ;
		token->code = WORD;
		token->string = ft_strdup(&s++[0]);
		lst_add_end(head, lst_new_node(token));
	}
}