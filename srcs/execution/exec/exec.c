/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:43:15 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/25 21:05:47 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_child(t_cmd *cmd, t_env **env)
{
	char	**envp_exec;

	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin_child(cmd, env);
		exit(0);
	}
	if (apply_redirections(cmd->redir, cmd) == -1)
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
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (0);
    if (cmd->argv[0][0] == '\0')
    {
        ft_putendl_fd("minishell: : command not found", 2);
        return (127);
    }
    if (prepare_heredocs(cmd->redir, cmd) == -1)
        return (130);
	// REBUILD ARGV()
		//	EXPAND(ARGV_ANTIGO)
		//	STRING = JUNTAR TODOS OS ARGVS EM UMA STRING
		//	NOVO ARGV = SPLIT (STRTING)
    if (is_builtin(cmd->argv[0]))
        return (exec_builtin_parent(cmd, env));
    cmd->path = get_path_dirs(cmd, env);
    if (!cmd->path)
    {
        ft_putendl_fd("minishell: command not found", 2);
        return (127);
    }
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

int exec_single_ast(t_ast *node, t_env **env)
{
    t_msh_ast	*data;
    t_cmd 		cmd;
    int			result;

    result = 0;
    if (!node || !node->content)
        return (0);
    data = (t_msh_ast *)node->content;
    if (!data->argv)
        return (1);
    cmd.argv = data->argv;
    cmd.path = data->path;
    cmd.heredoc_fd = -1;
    cmd.next = NULL;
    cmd.redir = NULL;
    if (data->redir && *data->redir)
        cmd.redir = convert_redir_list(*data->redir);
    result = ft_exec_cmd(&cmd, env);
    if (cmd.redir)
        free_exec_redir_list(cmd.redir);
    if (cmd.path && cmd.path != data->path)
        free(cmd.path);
    return (result);
}
