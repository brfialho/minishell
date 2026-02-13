/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:10:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/12 22:13:56 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*lst_cut(t_list **head, t_list *node)
{
	t_list	*lst;

	if (*head == node)
	{
		*head = (*head)->next;
		node->next = NULL;
		return (node);
	}
	lst = *head;
	while (lst)
	{
		if (lst->next == node)
		{
			lst->next = NULL;
			node->next = NULL;
			return (node);
		}
		lst = lst->next;
	}
	return (NULL);
}

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
	if (((t_token *)lower_prec_node->content)->precedence == 0)
		return (NULL);
	return (lower_prec_node);
}

// NAO FUNCIONA SEM WORDS NA BEIRA
// NAO TA COLOCANDO O CONTENT CERTO
// NAO TRATA ERRO
// ESTA IGNORANDO TODAS AS WORDS MENOS A PRIMEIRA NA LEAG
// TEM LEAK

void	print_ast_visual(t_ast *ast, int depth, char *prefix, int is_left)
{
    if (ast == NULL)
        return ;
    ft_printf("%s", prefix);
    if (depth > 0)
        ft_printf("%s", is_left ? "├── " : "└── ");
    ft_printf("%s\n", ((t_token *)ast->content)->string);
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

// static void	del_token(void	*content)
// {
// 	t_token	*token;

// 	token = content;
// 	if (token->code == WORD)
// 		free(token->string);
// 	free(token);
// }



t_ast	*ast_builder(t_list *token_lst)
{
	t_ast	*node;
	t_list	*lower_prec;
	t_list	*right;

	lower_prec = get_lower_prec(token_lst);
	if (lower_prec == NULL)
	{
		node = ast_new_node(token_lst->content);
		free (token_lst);
		return (node);
	}
	node = ast_new_node(lower_prec->content);
	right = lower_prec->next;
	free(lst_cut(&token_lst, lower_prec));
	node->left = ast_builder(token_lst);
	node->right = ast_builder(right);
	return (node);
}



int	parser(t_lexer *lexer)
{
	t_list	*token_lst;
	t_ast	**root;

	root = safe_calloc(1, sizeof(t_ast *));
	token_lst = lst_dup(*lexer->token_lst, NULL);

	*root = ast_builder(token_lst);
	ast_for_each(*root, read_ast_content);
	// print_ast_visual(*root, 0, "", 0);
	ast_del_all(root, NULL);
	free(root);
	// int i = lst_size(*lexer->token_lst);
	// while (i--)
	// {
	// }
	return (0);
}
