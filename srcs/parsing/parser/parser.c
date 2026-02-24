/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:10:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 04:07:17 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_ast_visual(t_ast *ast, int depth, char *prefix, int is_left)
{
	int		i;
	char	*string;

    if (ast == NULL)
        return ;
    ft_printf("%s", prefix);
    if (depth > 0)
		ft_printf("%s", is_left ? "├── " : "└── ");

	string = ((t_msh_ast *)ast->content)->str;
	if (((t_msh_ast *)ast->content)->type == NODE_EXEC)
	{
		i = 0;
		string = ft_strdup("");
		while (((t_msh_ast *)ast->content)->argv[i])
			string = ft_strjoin(ft_strjoin(string, ((t_msh_ast *)ast->content)->argv[i++]), "; ");
		string = ft_strjoin(string, ":");
		t_list *redir = *((t_msh_ast *)ast->content)->redir;
		while (redir)
		{
			string = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(string, ((t_redir *)redir->content)->target), "-"), ft_itoa(((t_redir *)redir->content)->type)), " ");
			redir = redir->next;
		}
	}
    ft_printf("%s:%d\n", string, ((t_msh_ast *)ast->content)->type);
    char *new_prefix;
    if (depth == 0)
        new_prefix = ft_strdup("");
    else
        new_prefix = ft_strjoin(prefix, is_left ? "│   " : "    ");
    print_ast_visual(ast->left, depth + 1, new_prefix, 1);
    print_ast_visual(ast->right, depth + 1, new_prefix, 0);
    free(new_prefix);
}

void	read_ast_content(void *content)
{
	ft_printf("%s\n", ((t_token *)content)->string);
}

void	parser(t_ast ***root, t_lexer *lexer)
{
	t_list	*token_lst;

	*root = ft_safe_calloc(1, sizeof(t_ast *));
	token_lst = lst_dup(*lexer->token_lst, NULL);
	**root = ast_builder(token_lst);
	// ast_for_each(**root, read_ast_content);
	print_ast_visual(**root, 0, "", 0);
}
