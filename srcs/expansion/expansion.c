/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:01 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/12 15:03:55 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "parser.h"

static char	*get_full_argv_str(char **old_argv);

char	**expand_argv(char **old_argv, t_env **env)
{
	char	**argv;
	char	*full_argv;
	int		i;

	old_argv = ft_split_deep_dup(old_argv);
	if (*old_argv == NULL)
		return (old_argv);
	i = -1;
	while (old_argv[++i])
		mark_protected_quotes(old_argv[i]);
	i = -1;
	while (old_argv[++i])
		old_argv[i] = expand_string(old_argv[i], FALSE, env);
	full_argv = get_full_argv_str(old_argv);
	ft_split_free(old_argv);
	argv = split_unprotected_spaces(full_argv, ' ');
	free(full_argv);
	i = -1;
	while (argv[++i])
		argv[i] = trim_quotes(argv[i]);
	return (argv);
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
		{
			ft_printf("Minishell: '%s': ambigous redirect\n",
				((t_redir *)lst->content)->target);
			return (EXIT_FAILURE);
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

t_bool	expand_redir(t_redir *redir, t_env **env)
{
	char	**word_split;

	if (!ft_str_charcount(redir->target, '$'))
		return (EXIT_SUCCESS);
	mark_protected_quotes(redir->target);
	redir->target = expand_string(redir->target, FALSE, env);
	word_split = split_unprotected_spaces(redir->target, ' ');
	if (ft_split_len(word_split) != 1)
		return (ft_split_free(word_split), EXIT_FAILURE);
	redir->target = trim_quotes(word_split[0]);
	free(word_split);
	return (EXIT_SUCCESS);
}

void	expand_heredoc(t_redir *redir, t_env **env)
{
	if (redir->type != REDIR_HEREDOC)
		return ;
	redir->target = expand_string(redir->target, TRUE, env);
}

static char	*get_full_argv_str(char **old_argv)
{
	char	*full_argv;
	int		i;

	i = 0;
	full_argv = ft_strdup(old_argv[i]);
	while (old_argv[++i])
	{
		full_argv = ft_strjoin_free(full_argv, " ", TRUE, FALSE);
		full_argv = ft_strjoin_free(full_argv, old_argv[i], TRUE, FALSE);
	}
	return (full_argv);
}
