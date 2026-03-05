/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:01 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 23:17:10 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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

char	*expand_redir(char	*old_str)
{
	ft_printf("OLD: %s\n", old_str);
	mark_protected_quotes(old_str);
	ft_printf("MARK: %s\n", old_str);
	old_str = expand_string(old_str);
	ft_printf("EXPAND: %s\n", old_str);
	// word_split = split_unprotected_spaces(old_str, ' ');
	return (old_str);	
}

