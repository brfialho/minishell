/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:06:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/14 02:02:47 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		heredoc_recursion(t_ast *root);
static void		heredoc(t_redir *redir);
static t_bool	check_for_quotes(char *s);

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

	if (check_for_quotes(redir->target))
	{
		redir->target = trim_quotes(redir->target, '\'', '"');
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
		ft_printf("Minishell: warning: heredoc"
			" delimited by EOF (wanted '%s')\n", redir->target);
	free(redir->target);
	redir->target = heredoc_string;
}

static t_bool	check_for_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (ft_str_charcount("'\"", s[i]))
			return (TRUE);
	return (FALSE);
}
