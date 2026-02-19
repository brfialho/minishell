/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:02:08 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 13:13:34 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_cmd	*convert_ast_pipeline(t_ast *node)
{
	t_msh_ast	*data;

	if (!node)
		return (NULL);
	data = node->content;
	if (data->type == NODE_PIPE)
	{
		t_cmd	*left;
		t_cmd	*right;

		left = convert_ast_pipeline(node->left);
		right = convert_ast_pipeline(node->right);
		left = cmd_add_back(left, right);
		return (left);
	}
	else
		return (create_cmd_from_ast(node));
}

int	exec_pipeline_ast(t_ast *node, t_env **env)
{
	t_cmd	*list;
	int		status;

	list = convert_ast_pipeline(node);
	status = exec_pipeline_list(list, env);
	ft_cleaner_list(list);
	return (status);
}

