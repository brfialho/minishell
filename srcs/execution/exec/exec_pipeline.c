/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:07:51 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/01 21:23:51 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"

static void	setup_and_exec_pipeline_child(t_cmd *cmd, int *pipe_fd, 
	int prev_fd, t_env **env)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	exec_child(cmd, env);
}

static pid_t	execute_pipeline_iteration(t_cmd *cmd, int *prev_fd, t_env **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (setup_pipe_if_needed(pipe_fd, cmd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		cleanup_pipe_on_fork_error(pipe_fd, cmd);
		return (-1);
	}
	if (pid == 0)
		setup_and_exec_pipeline_child(cmd, pipe_fd, *prev_fd, env);
	update_prev_fd(prev_fd, pipe_fd, cmd);
	return (pid);
}

int	exec_pipeline_list(t_cmd *cmd, t_env **env)
{
	int		prev_fd;
	pid_t	last_pid;
	pid_t	pid;

	prev_fd = -1;
	resolve_pipeline_paths(cmd, env);
	while (cmd)
	{
		pid = execute_pipeline_iteration(cmd, &prev_fd, env);
		if (pid == -1)
		{
			if (prev_fd != -1)
				close(prev_fd);
			return (1);
		}
		if (!cmd->next)
			last_pid = pid;
		cmd = cmd->next;
	}
	return (wait_for_last_pid(last_pid));
}
