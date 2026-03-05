/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:01 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/05 18:36:16 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "parser.h"


// 	CHECK FREE IN EXPAND STR
// 	CHECK FREE IN TRIM QUOTES
//	CHECK IF FREE ORIGINAL STR

char	**expand_argv(char **old_argv, t_env **env)
{
	char	**argv;
	char	*full_argv;
	int		i;

	// DUP ARGV
	i = -1;
	while (old_argv[++i])
		mark_protected_quotes(old_argv[i]);
	i = -1;
	while (old_argv[++i])
		old_argv[i] = expand_string(old_argv[i], FALSE, env);
	i = 0;
	full_argv = ft_strdup(old_argv[i]);
	while (old_argv[++i])
	{
		full_argv = ft_strjoin_free(full_argv, " ", TRUE, FALSE);
		full_argv = ft_strjoin_free(full_argv, old_argv[i], TRUE, FALSE); 
	}
	argv = split_unprotected_spaces(full_argv, ' ');
	i = -1;
	while (argv[++i])
		argv[i] = trim_quotes(argv[i]);
	free(full_argv);
	// ft_split_print(argv);
	return (argv);
}

t_bool	expand_redir(t_redir *redir, t_env **env)
{
	char	**word_split;

	// DUP ALL
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
	// DUP ALL
	if (redir->type != REDIR_HEREDOC)
		return ;
	mark_protected_quotes(redir->target);
	redir->target = expand_string(redir->target, TRUE, env);
}

