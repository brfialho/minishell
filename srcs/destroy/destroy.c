/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:05:10 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 18:07:38 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	del_ast_node(void *content);

void	destroy_cicle(t_mini *mini)
{
	lexer_destroy(&mini->lexer);
	ast_del_all(mini->root, del_ast_node);
	free(mini->root);
}

static void	del_ast_node(void *content)
{
	t_msh_ast	*ast;

	ast = content;
	if (ast->type == NODE_EXEC)
	{
		free(ast->argv);
		lst_del_all(ast->redir, free);
		free(ast->redir);
	}
	free (content);
}
