/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 15:50:35 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_status_shell = 0;

void	del_ast_node(void *content)
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

void parser_destroy(t_ast **root)
{
	ast_del_all(root, del_ast_node);
	free(root);
}

void	print_node(void *content)
{
	ft_printf("Code: %d String: %s\n", ((t_token *)content)->code, ((t_token *)content)->string);
}

void	del(void *content)
{
	t_token *token = content;

	if (token->code == WORD)
		free(token->string);
	free(token);
}

int main(int argc, char **argv)
{
	(void) argc;
	t_lexer lexer_data;

	ft_printf("%s\n", argv[1]);
	ft_lexer(&lexer_data, argv[1]);
	t_ast **root = parser(&lexer_data);
	// if (lexer_data.token_lst)
	// 	lst_for_each(*(t_list **)(lexer_data.token_lst), print_node);
	lexer_destroy(&lexer_data);
	parser_destroy(root);
}
