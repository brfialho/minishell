/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:02:08 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/24 20:43:33 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"

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

	status = 0;
	list = convert_ast_pipeline(node);
	status = exec_pipeline_list(list, env);
	ft_cleaner_list(list);
	return (status);
}

t_cmd	*create_cmd_from_ast(t_ast *node)
{
	t_msh_ast	*data;
	t_cmd		*cmd;

	if (!node || !node->content)
		return (NULL);
	data = node->content;
	cmd = safe_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = data->argv;
	cmd->path = data->path;
	cmd->redir = convert_redir_list(*data->redir);
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	return (cmd);
}
