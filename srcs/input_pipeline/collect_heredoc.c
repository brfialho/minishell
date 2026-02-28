/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 17:21:54 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/27 17:23:24 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	heredoc(t_redir *redir);
static char	*trim_heredoc(char *s);

void	collect_heredocs(t_ast *root)
{
	t_list	*lst;

	if (root == NULL)
		return ;
	if (((t_msh_ast *)root->content)->type == NODE_EXEC)
	{
		lst = *((t_msh_ast *)root->content)->redir;
		while (lst)
		{
			if (((t_redir *)lst->content)->type == REDIR_HEREDOC)
				heredoc(lst->content);
			lst = lst->next;
		}
	}
	collect_heredocs(root->left);
	collect_heredocs(root->right);
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
	while (ft_strcmp(redir->target, line))
	{
		heredoc_string = ft_strjoin_free(heredoc_string , ft_strjoin(line, "\n"), TRUE, TRUE);
		free(line);
		line = readline("> ");
	}
	free(line);
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
