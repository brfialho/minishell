/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:22:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/27 16:56:56 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*trim_heredoc(char *s)
{
	char	*new;
	
	new = ft_safe_calloc(ft_strlen(s) - 2 + 1, sizeof(char));
	ft_memcpy(new, s + 1, ft_strlen(s) - 2);
	free(s);
	return (new);
}

void	heredoc(t_redir *redir)
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

t_bool	parsing(t_mini *mini)
{
	mini->error_code = NO_ERROR;
	mini->error_code = ft_lexer(&mini->lexer, mini->input);
	if (mini->error_code)
		return (lexer_error_handler(mini), EXIT_FAILURE);
	trim_quoted_tokens(&mini->lexer);
	mini->error_code = parser(&mini->root, &mini->lexer);
	if (mini->error_code)
		return (parser_error_handler(mini), EXIT_FAILURE);
	collect_heredocs(*mini->root);
	return (EXIT_SUCCESS);
}
