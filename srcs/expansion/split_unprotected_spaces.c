/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_unprotected_spaces.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:46:58 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/14 01:42:19 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static t_bool	fill_split(char **split, char *s);
static int		count_words(char *s);
static char		get_state(char c, t_bool reset);

char	**split_unprotected_spaces(char *s)
{
	char	**split;

	get_state(0, TRUE);
	split = ft_calloc(count_words(s) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	get_state(0, TRUE);
	if (fill_split(split, s))
		ft_split_free(split);
	return (split);
}

static t_bool	fill_split(char **split, char *s)
{
	int		word;
	int		len;

	while (ft_str_charcount(WHITESPACE, *s))
		s++;
	word = 0;
	len = 0;
	while (*s)
	{
		len = 0;
		while (s[len] && (get_state(s[len], FALSE)
			|| !ft_str_charcount(WHITESPACE, s[len])))
			len++;
		split[word] = ft_substr(s, 0, len);
		if (!split[word++])
			return (EXIT_FAILURE);
		s += len;
		while (*s && ft_str_charcount(WHITESPACE, *s))
			s++;
	}
	return (EXIT_SUCCESS);
}

static int	count_words(char *s)
{
	int		count;

	count = 0;
	if (!*s)
		return (0);
	if (!ft_str_charcount(WHITESPACE, *s))
		count++;
	while (*s)
	{
		if (get_state(*s, FALSE) == 0
			&& ft_str_charcount(WHITESPACE, *s) && *(s + 1)
			&& !ft_str_charcount(WHITESPACE, *(s + 1)))
			count++;
		s++;
	}
	return (count);
}

static char	get_state(char c, t_bool reset)
{
	static int	state = 0;

	if (state && state == c)
		state = 0;
	else if (state == 0 && (c == S_QUOTE || c == D_QUOTE))
		state = c;
	if (reset)
		state = 0;
	return (state);
}
