/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:22:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 05:04:36 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_int8	check_redirs(t_list *lst)
{
	while(lst)
	{
		if (!ft_strlen(((t_redir *)lst->content)->target))
			return (((t_redir *)lst->content)->type);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

t_int8	validate_parsed_syntax(t_ast *root)
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
	left = validate_parsed_syntax(root->left);
	right = validate_parsed_syntax(root->right);
	return (left * (left != 0) + right * (left == 0 && right != 0));
}

t_bool	parsing(t_mini *mini)
{
	if (ft_lexer(&mini->lexer, mini->input))
		return (EXIT_FAILURE);
	trim_quoted_tokens(&mini->lexer);
	parser(&mini->root, &mini->lexer);
	ft_printf("SYNTAX:%d\n", validate_parsed_syntax(*mini->root));
	return (EXIT_SUCCESS);
}
