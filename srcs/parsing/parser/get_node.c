/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:41:50 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/22 03:27:44 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_argv(t_msh_ast *content, t_list **token_lst);
static void	parse_redir(t_list **redir, t_list **token_lst);

t_ast	*get_operator_node(t_token *token)
{
	t_msh_ast	*content;

	content = ft_safe_calloc(1, sizeof(t_msh_ast));
	if (token->code == PIPE)
		content->type = NODE_PIPE;
	else if (token->code == LOGICAL_AND)
		content->type = NODE_AND;
	else if (token->code == LOGICAL_OR)
		content->type = NODE_OR;
	content->str = token->string;
	return (ast_new_node(content));
}

t_ast	*get_exec_node(t_list *token_lst)
{
	t_msh_ast	*content;
	t_list		*lst;
	int			i;

	content = ft_safe_calloc(1, sizeof(t_msh_ast));
	content->argv = ft_safe_calloc(lst_size(token_lst) + 1, sizeof(char *));
	content->redir = ft_safe_calloc(1, sizeof(t_list *));
	content->type = NODE_EXEC;
	lst = token_lst;
	i = 0;
	while(lst)
	{	
		if (((t_token *)lst->content)->code < 5)
			parse_redir(content->redir, &lst);
		else
			parse_argv(content, &lst);
	}
	lst_del_all(&token_lst, NULL);
	return (ast_new_node(content));
}

static void	parse_redir(t_list **redir, t_list **token_lst)
{
	t_redir	*redir_node;

	redir_node = ft_safe_calloc(1, sizeof(t_redir));
	redir_node->type = (int)((t_token *)(*token_lst)->content)->code;
	*token_lst = (*token_lst)->next;
	if (*token_lst)
	{
		redir_node->target = ((t_token *)(*token_lst)->content)->string;
		*token_lst = (*token_lst)->next;
	}
	lst_add_end(redir, lst_new_node(redir_node));
}

static void	parse_argv(t_msh_ast *content, t_list **token_lst)
{
	int		i;
	char	*arg;

	i = 0;
	while (content->argv[i])
		i++;
	arg = ft_strdup("");
	while (*token_lst && ((t_token *)(*token_lst)->content)->code == WORD)
	{
		arg = ft_strjoin_free(arg, ((t_token *)(*token_lst)->content)->string, TRUE, FALSE);
		if (((t_token *)(*token_lst)->content)->space_next == TRUE)
		{
			*token_lst = (*token_lst)->next;
			break;
		}
		*token_lst = (*token_lst)->next;
	}
	content->argv[i] = arg;
}
