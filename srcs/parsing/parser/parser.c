/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:10:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/12 20:14:41 by brfialho         ###   ########.fr       */
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
	t_list *token_lst;
	t_list *lower_prec_node;
	// t_ast_node	**root;

	// root = safe_calloc(1, sizeof(t_ast_node *));
	int i = lst_size(*lexer->token_lst);
	token_lst = lst_dup(*lexer->token_lst, NULL);
	while (i--)
	{
		lower_prec_node = get_lower_prec(token_lst);
		t_token * token = lower_prec_node->content;
		ft_printf("TOKEN: %s PREC: %d\n", token->string, token->precedence);
		free (lst_detach(&token_lst, lower_prec_node));
	}
	return (0);
}
