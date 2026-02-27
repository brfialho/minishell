/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:38:28 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/22 02:40:53 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_list	*get_lower_prec(t_list *token_lst);
static t_list	*mini_lst_cut(t_list **head, t_list *node);

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

static t_list	*get_lower_prec(t_list *token_lst)
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

static t_list	*mini_lst_cut(t_list **head, t_list *node)
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
