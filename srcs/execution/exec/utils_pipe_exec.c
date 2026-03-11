/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipeline_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 21:22:08 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/01 21:23:59 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"

int	setup_pipe_if_needed(int *pipe_fd, t_cmd *cmd)
{
	if (!cmd->next)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (-1);
	return (0);
}

void	cleanup_pipe_on_fork_error(int *pipe_fd, t_cmd *cmd)
{
	if (cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	update_prev_fd(int *prev_fd, int *pipe_fd, t_cmd *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

int	extract_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	wait_for_last_pid(pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		last_status;

	last_status = 0;
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
			last_status = status;
	}
	return (extract_exit_status(last_status));
}
