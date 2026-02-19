/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:42:40 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 12:09:43 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "export") == 0)
		return (1);
	if (strcmp(cmd, "unset") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int exec_single_ast(t_ast *node, t_env **env)
{
	t_msh_ast	*data;
	t_cmd 		cmd;

	if (!node || !node->content)
		return (0);
	data = (t_msh_ast *)node->content;
	cmd.argv = data->argv;
	cmd.path = data->path;
	cmd.redir = NULL;
	cmd.heredoc_fd = -1;
	cmd.next = NULL;
	return (ft_exec_cmd(&cmd, env));
}