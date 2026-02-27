/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:48:34 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/23 02:44:57 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	del_ast_content(void *content);
static void	del_redir_content(void *content);

void	parser_destroy(t_ast **root)
{
	ast_del_all(root, del_ast_content);
	free(root);
}

static void	del_ast_content(void *content)
{
	t_msh_ast	*ast;
	int			i;

	ast = content;
	if (ast->type == NODE_EXEC)
	{
		i = 0;
		while (ast->argv[i])
			free(ast->argv[i++]);
		free(ast->argv);
		lst_del_all(ast->redir, del_redir_content);
		free(ast->redir);
	}
	free(content);
}

static void	del_redir_content(void *content)
{
	t_redir	*redir;

	redir = content;
	free(redir->target);
	free(redir);
}
