/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:22:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/26 21:52:17 by brfialho         ###   ########.fr       */
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

t_bool	check_syntax(t_mini *mini)
{
	t_token_code	syntax_code;
	int				i;

	syntax_code = syntax_validator(*mini->root);
	if (syntax_code)
	{
		i = 0;
		while (mini->lexer.op_lst[i].code != syntax_code)
			i++;
		ft_printf(SYNTAX_ERROR " '%s'\n", mini->lexer.op_lst[i].str);
		lexer_destroy(&mini->lexer);
		parser_destroy(mini->root);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_bool	parsing(t_mini *mini)
{
	ft_lexer(&mini->lexer, mini->input);
	if (mini->lexer.unclosed_quotes)
		return (lexer_error_handler(&mini->lexer, mini->input), EXIT_FAILURE);
	parser(&mini->root, &mini->lexer);
	trim_quoted_tokens(&mini->lexer);
	if (check_syntax(mini))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
