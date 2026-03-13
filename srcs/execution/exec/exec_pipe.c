/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:07:51 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/12 22:20:12 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"
#include "main.h"

static void	setup_and_exec_pipeline_child(t_cmd *cmd, int *pipe_fd,
	int prev_fd, t_mini *mini)
{
	if (prev_fd != -1)
	{
		// dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		// dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	exec_child(cmd, &mini->env, mini);
}

static pid_t	execute_pipeline_iteration(t_cmd *cmd, int *prev_fd,
	t_cmd *head, t_mini *mini)
{
	int		pipe_fd[2];
	pid_t	pid;

	mini->current_cmd_head = head;
	if (setup_pipe_if_needed(pipe_fd, cmd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		cleanup_pipe_on_fork_error(pipe_fd, cmd);
		return (-1);
	}
	if (pid == 0)
		setup_and_exec_pipeline_child(cmd, pipe_fd, *prev_fd, mini);
	mini->current_cmd_head = NULL;
	update_prev_fd(prev_fd, pipe_fd, cmd);
	return (pid);
}

int	exec_pipeline_list(t_cmd *cmd, t_env **env, t_mini *mini)
{
	int		prev_fd;
	pid_t	last_pid;
	pid_t	pid;
	t_cmd	*lst;

	prev_fd = -1;
	resolve_pipeline_paths(cmd, env);
	lst = cmd;
	while (lst)
	{
		pid = execute_pipeline_iteration(lst, &prev_fd, cmd, mini);
		if (pid == -1)
		{
			if (prev_fd != -1)
				close(prev_fd);
			return (1);
		}
		if (!lst->next)
			last_pid = pid;
		lst = lst->next;
	}
	return (wait_for_last_pid(last_pid));
}
