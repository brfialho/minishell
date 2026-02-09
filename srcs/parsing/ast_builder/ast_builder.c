/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:10:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/09 18:49:18 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast_node	*parse_exec(t_list **lst)
{
	
}

t_ast_node	*parse_pipe(t_list **lst)
{
	t_ast_node	*node;

	node = parse_exec(lst);
	if (!node)
		return (parse_error(lst));
	if (((t_token *)*lst)->code == PIPE)
	{
		*lst = (*lst)->next;
		node = pipe_node(node, parse_exec);
	}
	return (node);
}

int	ast_builder(t_lexer *lexer)
{
	t_ast_node	**root;
	t_list		**lst;

	root = ft_calloc(1, sizeof(t_ast_node *));
	if (!root)
		return (FALSE);
	lst = ft_calloc (1, sizeof(t_list *));
	if (!lst)
		return (free(root), FALSE);
	*lst = lexer->token_lst;
	while (*lst)
	{
		*root = parse_pipe(lst);
	}
}