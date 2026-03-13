/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:10:09 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/13 19:12:09 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "main.h"
#include "expansion.h"

void	exec_child(t_cmd *cmd, t_env **env, t_mini *mini)
{
	char	**envp_exec;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->argv[0]))
		exec_builtin_child(cmd, env, mini);
	if (apply_redirections(cmd->redir, cmd) == -1)
		exit(1);
	if (cmd->heredoc_fd != -1)
		dup2(cmd->heredoc_fd, STDIN_FILENO);
	envp_exec = env_to_envp(*env);
	if (!envp_exec)
		exit(1);
	if (!cmd->path)
		cmd->path = ft_strdup("");
	execve(cmd->path, cmd->argv, envp_exec);
	perror(cmd->argv[0]);
	free_envp(envp_exec);
	env_clear(&mini->env);
	ft_cleaner_list(mini->current_cmd_head);
	parser_destroy(mini->root);
	exit(127);
}

static int	exec_external_cmd(t_cmd *cmd, t_env **env, t_mini *mini)
{
	pid_t	pid;
	int		status;
	char	*value;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		mini->current_cmd_head = cmd;
		exec_child(cmd, env, mini);
	}
	waitpid(pid, &status, 0);
	value = ft_itoa(status / 256);
	ft_set_env(env, "?", value);
	free(value);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	ft_exec_cmd(t_cmd *cmd, t_env **env, t_mini *mini)
{
	if (!cmd->argv[0] || is_builtin(cmd->argv[0]))
		return (exec_builtin_parent(cmd, env, mini));
	cmd->path = get_path_dirs(cmd, env);
	if (!cmd->path)
	{
		ft_putendl_fd("minishell: command not found", 2);
		return (127);
	}
	return (exec_external_cmd(cmd, env, mini));
}

int	exec_node(t_ast *node, t_env **env, t_mini *mini)
{
	int			status;
	t_msh_ast	*data;

	if (!node || !node->content)
		return (0);
	data = (t_msh_ast *)node->content;
	if (data->type == NODE_EXEC)
		return (exec_single_ast(node, env, mini));
	if (data->type == NODE_PIPE)
		return (exec_pipeline_ast(node, env, mini));
	if (data->type == NODE_AND)
	{
		status = exec_node(node->left, env, mini);
		if (status == 0)
			return (exec_node(node->right, env, mini));
		return (status);
	}
	if (data->type == NODE_OR)
	{
		status = exec_node(node->left, env, mini);
		if (status != 0)
			return (exec_node(node->right, env, mini));
		return (status);
	}
	return (1);
}

int	exec_single_ast(t_ast *node, t_env **env, t_mini *mini)
{
	t_msh_ast	*data;
	t_cmd		*cmd;
	int			result;

	result = 0;
	if (!node || !node->content)
		return (0);
	data = (t_msh_ast *)node->content;
	if (!data->argv)
		return (1);
	if (expand_all_redir(data->redir, env))
		return (1);
	cmd = ft_safe_calloc(1, sizeof(t_cmd));
	cmd->argv = expand_argv(data->argv, env);
	cmd->heredoc_fd = -1;
	if (data->redir && *data->redir)
	cmd->redir = convert_redir_list(*data->redir);
	result = ft_exec_cmd(cmd, env, mini);
	destroy_exec_cmd(cmd);
	free(cmd);
	return (result);
}
