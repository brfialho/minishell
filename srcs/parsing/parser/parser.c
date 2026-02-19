/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:10:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 18:17:23 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
			string = ft_strjoin(ft_strjoin(string, ((t_msh_ast *)ast->content)->argv[i++]), " ");
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

// NAO TRATA ERRO

t_list	*mini_lst_cut(t_list **head, t_list *node)
{
	t_list	*lst;

	if (*head == node)
	{
		*head = NULL;
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

t_ast	*get_operator_node(t_token *token)
{
	t_msh_ast	*content;

	content = safe_calloc(1, sizeof(t_msh_ast));
	if (token->code == PIPE)
		content->type = NODE_PIPE;
	else if (token->code == LOGICAL_AND)
		content->type = NODE_AND;
	else if (token->code == LOGICAL_OR)
		content->type = NODE_OR;
	content->str = token->string;
	return (ast_new_node(content));
}

t_list	*parse_redir(t_list **redir, t_list *token_lst)
{
	t_redir	*redir_node;

	redir_node = safe_calloc(1, sizeof(t_redir));
	redir_node->type = (int)((t_token *)token_lst->content)->code;
	if (token_lst->next)
		redir_node->target = ((t_token *)token_lst->next->content)->string;
	lst_add_end(redir, lst_new_node(redir_node));
	if (token_lst->next)
		return (token_lst->next);
	return (token_lst);
}

// DOESNT WORK WITH INFILE
t_ast	*get_exec_node(t_list *token_lst)
{
	t_msh_ast	*content;
	t_list		*lst;
	int			i;

	content = safe_calloc(1, sizeof(t_msh_ast));
	content->argv = safe_calloc(lst_size(token_lst) + 1, sizeof(char *));
	content->redir = safe_calloc(1, sizeof(t_list *));
	content->type = NODE_EXEC;
	lst = token_lst;
	i = 0;
	while(lst)
	{	
		if (((t_token *)lst->content)->code < 5)
			lst = parse_redir(content->redir, lst);
		else
			content->argv[i++] = ((t_token *)lst->content)->string;
		lst = lst->next;
	}
	lst_del_all(&token_lst, NULL);
	return (ast_new_node(content));
}

t_ast	*ast_builder(t_list *token_lst)
{
	t_ast	*node;
	t_list	*lower_prec;
	t_list	*right;

	if (token_lst == NULL)
		return (NULL);
	lower_prec = get_lower_prec(token_lst);
	if (lower_prec == NULL)
		return (get_exec_node(token_lst));
	node = get_operator_node(lower_prec->content);
	right = lower_prec->next;
	free(mini_lst_cut(&token_lst, lower_prec));
	node->left = ast_builder(token_lst);
	node->right = ast_builder(right);
	return (node);
}

t_ast	**parser(t_lexer *lexer)
{
	t_list	*token_lst;
	t_ast	**root;

	root = safe_calloc(1, sizeof(t_ast *));
	token_lst = lst_dup(*lexer->token_lst, NULL);
	*root = ast_builder(token_lst);
	// ast_for_each(*root, read_ast_content);
	print_ast_visual(*root, 0, "", 0);
	return (root);
}
