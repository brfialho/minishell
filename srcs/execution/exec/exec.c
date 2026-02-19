/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:43:15 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 19:29:19 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	exec_child(t_cmd *cmd, t_env **env)
{
	char	**envp_exec;

	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin_child(cmd, env);
		exit(0);
	}
	if (set_redir(cmd->redir, cmd) == -1)
		exit(1);
	if (cmd->heredoc_fd != -1)
		dup2(cmd->heredoc_fd, STDIN_FILENO);
	envp_exec = env_to_envp(*env);
	if (!envp_exec)
		exit(1);
	execve(cmd->path, cmd->argv, envp_exec);
	perror(cmd->argv[0]);
	free_envp(envp_exec);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

static int	exec_external_cmd(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		exec_child(cmd, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	ft_exec_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0]) // perguntar se ast guarda redirect
		return (0);
	if (cmd->argv[0][0] == '\0')
	{
		ft_putendl_fd("minishell: : command not found", 2);
		return (127);
	}
	if (is_builtin(cmd->argv[0]))
		return (exec_builtin_parent(cmd, env));
	return (exec_external_cmd(cmd, env));
}

int exec_node(t_ast *node, t_env **env)
{
	int			status;
	t_msh_ast	*data;

	if (!node || !node->content)
		return (0);
	data = (t_msh_ast *)node->content;
	if (data->type == NODE_EXEC)
		return (exec_single_ast(node, env));
	if (data->type == NODE_PIPE)
		return (exec_pipeline_ast(node, env));
	if (data->type == NODE_AND)
	{
		status = exec_node(node->left, env);
		if (status == 0)
			return (exec_node(node->right, env));
		return status;
	}
	if (data->type == NODE_OR)
	{
		status = exec_node(node->left, env);
		if (status != 0)
			return (exec_node(node->right, env));
		return status;
	}
	return (1);
}
