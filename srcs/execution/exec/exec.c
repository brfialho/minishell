/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:43:15 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/06 16:10:21 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "main.h"

void	exec_child(t_mini *mini, t_cmd *cmd, t_env **env)
{
	char	**envp_exec;

	if (!cmd->argv || !cmd->argv[0])
    	exit(0);
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

static int	exec_external_cmd(t_mini *mini, t_cmd *cmd, t_env **env)
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
		exec_child(mini, cmd, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	ft_exec_cmd(t_mini *mini, t_cmd *cmd, t_env **env)
{
    if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
    	return (0) ;
	if (cmd->argv[0][0] == '\0')
	{
		ft_putendl_fd("minishell: : command not found", 2);
		return (127);
	}
	ft_printf("CMD: [%s]\n", cmd->argv[0]);
    if (is_builtin(cmd->argv[0]))
        return (exec_builtin_parent(cmd, env));
    cmd->path = get_path_dirs(cmd, env);
    if (!cmd->path)
    {
        ft_putendl_fd("minishell: command not found", 2);
        return (127);
    }
    return (exec_external_cmd(mini, cmd, env));
}

int exec_node(t_mini *mini, t_ast *node, t_env **env)
{
	int			status;
	t_msh_ast	*data;

	if (!node || !node->content)
		return (0);
	data = (t_msh_ast *)node->content;
	if (data->type == NODE_EXEC)
		return (exec_single_ast(mini, node, env));
	if (data->type == NODE_PIPE)
		return (exec_pipeline_ast(mini, node, env));
	if (data->type == NODE_AND)
	{
		status = exec_node(mini, node->left, env);
		if (status == 0)
			return (exec_node(mini, node->right, env));
		return status;
	}
	if (data->type == NODE_OR)
	{
		status = exec_node(mini, node->left, env);
		if (status != 0)
			return (exec_node(mini, node->right, env));
		return status;
	}
	return (1);
}

t_bool	expand_all_redir(t_list **redir_lst, t_env **env)
{
	t_list	*lst;
	t_bool	error;

	lst = *redir_lst;
	error = FALSE;
	while (lst)
	{
		if (((t_redir *)lst->content)->type == REDIR_HEREDOC)
			expand_heredoc(lst->content, env);
		else if (((t_redir *)lst->content)->type != REDIR_HEREDOC_NO_EXPANSION)
			error = expand_redir(lst->content, env);
		if (error)
			return(ft_printf("Minishell: $%d: ambigous redirect", ((t_redir *)lst->content)->target), error);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

int exec_single_ast(t_mini *mini, t_ast *node, t_env **env)
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
	if (expand_all_redir(data->redir, env))
		return 1;
	cmd.argv = expand_argv(data->argv, env);
    cmd.path = data->path;
    cmd.heredoc_fd = -1;
    cmd.next = NULL;
    cmd.redir = NULL;
    if (data->redir && *data->redir)
        cmd.redir = convert_redir_list(*data->redir);
    result = ft_exec_cmd(mini, &cmd, env);
    if (cmd.redir)
        free_exec_redir_list(cmd.redir);
    if (cmd.path && cmd.path != data->path)
        free(cmd.path);
    return (result);
}

// free argv
// free redir
