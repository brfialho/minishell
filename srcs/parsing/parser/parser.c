/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:10:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/10 20:38:01 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parser(t_lexer *lexer)
{
	t_ast_node	**root;
	t_list		**lst;

	root = safe_calloc(1, sizeof(t_ast_node *));
	lst = safe_calloc (1, sizeof(t_list *));
	*lst = *lexer->token_lst;
	while (*lst)
	{
		*root = parse_pipe(lst);
	}
}
