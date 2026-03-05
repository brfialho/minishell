/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:01 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 23:38:45 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "parser.h"

char	**expand_argv(char **old_argv)
{
	char	**argv;
	char	*full_argv;
	int		i;

	i = -1;
	while (old_argv[++i])
		mark_protected_quotes(old_argv[i]);
	i = -1;
	while (old_argv[++i])
		old_argv[i] = expand_string(old_argv[i]);
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
	ft_split_print(argv);
	return (argv);
}

t_bool	expand_redir(t_redir *redir)
{
	char	**word_split;

	ft_printf("OLD: %s\n", redir->target);
	mark_protected_quotes(redir->target);
	ft_printf("MARK: %s\n", redir->target);
	redir->target = expand_string(redir->target);
	ft_printf("EXPAND: %s\n", redir->target);
	word_split = split_unprotected_spaces(redir->target, ' ');
	if (ft_split_len(word_split) != 1)
		return (ft_split_free(word_split), EXIT_FAILURE);
	redir->target = trim_quotes(word_split[0]);
	free(word_split);
	return (EXIT_SUCCESS);	
}

