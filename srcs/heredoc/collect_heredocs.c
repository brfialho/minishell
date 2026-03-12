/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:06:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/12 14:58:23 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	heredoc_recursion(t_ast *root);
static void	heredoc(t_redir *redir);
static char	*trim_heredoc(char *s);

t_error	collect_heredocs(t_mini *mini)
{
	t_error	error;

	error = NO_ERROR;
	rl_event_hook = shell_signal_hook;
	heredoc_recursion(*mini->root);
	if (g_shell_signal == SIGINT)
		error = HEREDOC_SIGINT;
	rl_event_hook = NULL;
	return (error);
}

static void	heredoc_recursion(t_ast *root)
{
	t_list	*lst;

	if (root == NULL)
		return ;
	if (((t_msh_ast *)root->content)->type == NODE_EXEC)
	{
		lst = *((t_msh_ast *)root->content)->redir;
		while (lst)
		{
			if (g_shell_signal == SIGINT)
				return ;
			if (((t_redir *)lst->content)->type == REDIR_HEREDOC)
				heredoc(lst->content);
			lst = lst->next;
		}
	}
	heredoc_recursion(root->left);
	heredoc_recursion(root->right);
}

static void	heredoc(t_redir *redir)
{
	char	*heredoc_string;
	char	*line;

	if (*redir->target == '\'' || *redir->target == '"')
	{
		redir->target = trim_heredoc(redir->target);
		redir->type = REDIR_HEREDOC_NO_EXPANSION;
	}
	heredoc_string = ft_strdup("");
	line = readline("> ");
	while (line && ft_strcmp(redir->target, line))
	{
		heredoc_string = ft_strjoin_free(heredoc_string,
				ft_strjoin(line, "\n"), TRUE, TRUE);
		if (g_shell_signal == SIGINT)
			break ;
		line = readline("> ");
	}
	if (!line)
		ft_printf("Minishell: warning: heredoc delimited by EOF (wanted '%s')\n", redir->target);
	free(redir->target);
	redir->target = heredoc_string;
}

static char	*trim_heredoc(char *s)
{
	char	*new;

	new = ft_safe_calloc(ft_strlen(s) - 2 + 1, sizeof(char));
	ft_memcpy(new, s + 1, ft_strlen(s) - 2);
	free(s);
	return (new);
}
