/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 22:27:02 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/26 22:28:13 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_int8	check_redirs(t_list *lst);

t_int8	syntax_validator(t_ast *root)
{
	t_msh_ast	*content;
	t_int8		left;
	t_int8		right;

	if (root == NULL)
		return (EXIT_SUCCESS);
	content = root->content;
	if (content->type != NODE_EXEC
		&& (root->left == NULL || root->right == NULL))
		return (content->type);
	if (content->type == NODE_EXEC)
		return (check_redirs(*content->redir));
	left = syntax_validator(root->left);
	right = syntax_validator(root->right);
	return (left * (left != 0) + right * (left == 0 && right != 0));
}

static t_int8	check_redirs(t_list *lst)
{
	while(lst)
	{
		if (!ft_strlen(((t_redir *)lst->content)->target))
			return (((t_redir *)lst->content)->type);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
