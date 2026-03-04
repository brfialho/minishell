/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_unprotected.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:46:58 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 19:50:04 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static t_bool	fill_split(char **split, char *s, char c);
static int		count_words(char *s, char c);
static char		get_state(char c, t_bool reset);

char	**split_unprotected_spaces(char *s, char c)
{
	char	**split;

	get_state(0, TRUE);
	split = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	get_state(0, TRUE);
	if (fill_split(split, s, c))
		ft_split_free(split);
	return (split);
}

static t_bool	fill_split(char **split, char *s, char c)
{
	int		word;
	int		len;

	while (*s == c)
		s++;
	word = 0;
	len = 0;
	while (*s)
	{
		len = 0;
		while (s[len] && (get_state(s[len], FALSE) || s[len] != c))
			len++;
		split[word] = ft_substr(s, 0, len);
		if (!split[word++])
			return (EXIT_FAILURE);
		s += len;
		while (*s && *s == c)
			s++;
	}
	return (EXIT_SUCCESS);
}

static int	count_words(char *s, char c)
{
	int		count;

	count = 0;
	if (!*s)
		return (0);
	if (*s != c)
		count++;
	while (*s)
	{
		if (get_state(*s, FALSE) == 0
			&& *s == c && *(s + 1) && *(s + 1) != c)
			count++;
		s++;
	}
	return (count);
}

static char	get_state(char c, t_bool reset)
{
	static int state = 0;

	if (state && state == c)
		state = 0;
	else if (state == 0 && (c == S_QUOTE || c == D_QUOTE))
		state = c;
	if (reset)
		state = 0;
	return (state);
}
