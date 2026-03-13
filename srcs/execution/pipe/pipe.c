/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:02:08 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/12 21:16:12 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"
#include "expansion.h"
#include "main.h"

t_cmd	*convert_ast_pipeline(t_ast *node, t_env **env)
{
	t_msh_ast	*data;
	t_cmd		*left;
	t_cmd		*right;

	if (!node)
		return (NULL);
	data = node->content;
	if (data->type == NODE_PIPE)
	{
		left = convert_ast_pipeline(node->left, env);
		right = convert_ast_pipeline(node->right, env);
		left = cmd_add_back(left, right);
		return (left);
	}
	else
		return (create_cmd_from_ast(node, env));
}

int	exec_pipeline_ast(t_ast *node, t_env **env, t_mini *mini)
{
	t_cmd	*list;
	int		status;

	status = 0;
	list = convert_ast_pipeline(node, env);
	status = exec_pipeline_list(list, env, mini);
	ft_cleaner_list(list);
	return (status);
}

t_cmd	*create_cmd_from_ast(t_ast *node, t_env **env)
{
	t_msh_ast	*data;
	t_cmd		*cmd;

	if (!node || !node->content)
		return (NULL);
	data = node->content;
	cmd = ft_safe_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (expand_all_redir(data->redir, env))
		return (NULL);
	cmd->argv = expand_argv(data->argv, env);
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	cmd->redir = NULL;
	cmd->path = NULL;
	if (data->redir && *data->redir)
		cmd->redir = convert_redir_list(*data->redir);
	return (cmd);
}
