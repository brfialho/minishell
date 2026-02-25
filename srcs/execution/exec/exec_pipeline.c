/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:07:51 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/24 20:49:45 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"

static void	setup_and_exec_pipeline_child(t_cmd *cmd, int *pipe_fd, 
	int prev_fd, t_env **env)
{
	int	status;

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
	if (apply_redirections(cmd->redir, cmd) == -1)
		exit(1);
	status = ft_exec_cmd(cmd, env);
	exit(status);
}

static int	*execute_pipeline_iteration(t_cmd *cmd, int *prev_fd, t_env **env)
{
	static int	pipe_fd[2];

	if (cmd->next)
		pipe(pipe_fd);
	if (fork() == 0)
		setup_and_exec_pipeline_child(cmd, pipe_fd, *prev_fd, env);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
	return (pipe_fd);
}

int	exec_pipeline_list(t_cmd *cmd, t_env **env)
{
	int	prev_fd;
	int	status;
	int	last_status;

	prev_fd = -1;
	last_status = 0;
	if (!cmd || !cmd->argv || !cmd->argv[0]) // verificar se tem redirect na struct cmd 
		return (0);
	if (cmd->argv[0][0] == '\0')
	{
		ft_putendl_fd("minishell: : command not found", 2);
		return (127);
	}
	if (prepare_heredocs(cmd->redir, cmd) == -1)
		return (130);
	while (cmd)
	{
		execute_pipeline_iteration(cmd, &prev_fd, env);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		last_status = status;
	return (WEXITSTATUS(last_status));
}
