/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:37:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/09 12:54:01 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	apply_parent_redir(
	t_cmd *cmd,
	int *stdin_backup,
	int *stdout_backup
)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
		return (-1);
	if (set_redir(cmd->redir, cmd) == -1)
	{
		dup2(*stdin_backup, STDIN_FILENO);
		dup2(*stdout_backup, STDOUT_FILENO);
		close(*stdin_backup);
		close(*stdout_backup);
		return (-1);
	}
	return (0);
}

static void	apply_parent_heredoc(t_cmd *cmd)
{
	if (cmd->heredoc_fd != -1)
		dup2(cmd->heredoc_fd, STDIN_FILENO);
}

static void	cleanup_parent_fds(
	t_cmd *cmd,
	int stdin_backup,
	int stdout_backup
)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	if (cmd->heredoc_fd != -1)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
}

int	exec_builtin_parent(t_cmd *cmd, t_env **env)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;

	if (apply_parent_redir(cmd, &stdin_backup, &stdout_backup) == -1)
		return (1);
	apply_parent_heredoc(cmd);
	ret = execute_builtin(cmd, env);
	cleanup_parent_fds(cmd, stdin_backup, stdout_backup);
	return (ret);
}

void	exec_builtin_child(t_cmd *cmd, t_env **env)
{
	if (set_redir(cmd->redir, cmd) == -1)
		exit(1);
	if (cmd->heredoc_fd != -1)
		dup2(cmd->heredoc_fd, STDIN_FILENO);
	exit(execute_builtin(cmd, env));
}
