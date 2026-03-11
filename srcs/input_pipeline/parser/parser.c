/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:10:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 22:43:26 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_int8	parser(t_ast ***root, t_lexer *lexer)
{
	t_list	*token_lst;

	*root = ft_safe_calloc(1, sizeof(t_ast *));
	token_lst = lst_dup(*lexer->token_lst, NULL);
	**root = ast_builder(token_lst);
	return (syntax_validator(**root));
}
