/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:10:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/12 19:51:13 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*get_lower_prec(t_list *token_lst)
{
	t_list *lst;
	t_list *lower_prec_node;

	lst = token_lst;
	lower_prec_node = token_lst;
	while (lst)
	{
		if (((t_token *)lst->content)->precedence >= ((t_token *)lower_prec_node->content)->precedence)
			lower_prec_node = lst;
		lst = lst->next;
	}
	// if (((t_token *)lst->content)->precedence == 0)
	// 	return (NULL);
	return (lower_prec_node);
}

int	parser(t_lexer *lexer)
{
	// t_ast_node	**root;

	// root = safe_calloc(1, sizeof(t_ast_node *));
	t_token token;
	// int i = lst_size(*lexer->token_lst);
	// while (--i)
	// {
		token = (*(t_token *)get_lower_prec(*lexer->token_lst)->content);
		ft_printf("TOKEN: %s PREC: %d\n", token.string, token.precedence);
	// }
	return (0);
}
