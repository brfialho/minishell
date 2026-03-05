/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:01 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 21:41:10 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	mark_protected_quotes(char *s);
static char	*trim_quotes(char *old_str);

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

static void	mark_protected_quotes(char *s)
{
	char	state;

	state = 0;
	while (*s)
	{
		if (state && *s == state)
		{
			*s = (state == '\'') * S_QUOTE + (state == '"') * D_QUOTE;
			state = 0;
		}
		else if (state == 0 && (*s == '\'' || *s == '"'))
		{
			state = *s;
			*s = (state == '\'') * S_QUOTE + (state == '"') * D_QUOTE;
		}
		s++;
	}
}

static char	*trim_quotes(char *old_str)
{
	char	*new_str;
	char	*new;
	char	*old;
	char	state;

	new_str = ft_safe_calloc(ft_strlen(old_str) + 1, sizeof(char));
	new = new_str;
	old = old_str;
	state = 0;
	while (*old)
	{
		if (state && state == *old)
		{
			state = 0;
			old++;
		}
		else if (state == 0 && (*old == S_QUOTE || *old == D_QUOTE))
			state = *old++;
		else 
			*new++ = *old++;
	}
	free (old_str);
	return (new_str);
}
