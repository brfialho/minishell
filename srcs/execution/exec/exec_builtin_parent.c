/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:37:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/10 19:17:24 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "main.h"

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
	if (apply_redirections(cmd->redir, cmd) == -1)
	{
		dup2(*stdin_backup, STDIN_FILENO);
		dup2(*stdout_backup, STDOUT_FILENO);
		close(*stdin_backup);
		close(*stdout_backup);
		return (-1);
	}
	return (0);
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

int	exec_builtin_parent(t_cmd *cmd, t_env **env, t_mini *mini)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;
	int	is_parent_exit;
	char *value;

	is_parent_exit = 1;
	if (apply_parent_redir(cmd, &stdin_backup, &stdout_backup) == -1)
		return (1);
	ret = execute_builtin(cmd, env, is_parent_exit, mini);
	value = ft_itoa(ret);
	ft_set_env(env, "?", value);
	free(value);
	cleanup_parent_fds(cmd, stdin_backup, stdout_backup);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		exit(ret);
	return (ret);
}

void	exec_builtin_child(t_cmd *cmd, t_env **env, t_mini *mini)
{
	if (apply_redirections(cmd->redir, cmd) == -1)
		exit(1);
	execute_builtin(cmd, env, 0, mini);
	ft_split_free(cmd->argv);
	parser_destroy(mini->root);
	exit(0);
}
