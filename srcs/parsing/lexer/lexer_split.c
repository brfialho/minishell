/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:16:09 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/27 18:50:52 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	lexer_count_words(char const *s)
{
	size_t	words;
	t_state state;

	words = 0;
	state = DEFAULT;
	if (!*s)
		return (words);
	if (*s != ' ')
		words++;
	while (*s)
	{
		if (*s == '"' && state == DEFAULT)
			state = IN_D_QUOTES;
		else if (*s == '\'' && state == DEFAULT)
			state = IN_S_QUOTES;
		else if ((*s == '"' && state == IN_D_QUOTES) 
		|| (*s == '\'' && state == IN_S_QUOTES))
			state = DEFAULT;
		else if (*(s + 1) && *s == ' ' && *(s + 1) != ' ' && state == DEFAULT)
			words++;
		s++;
	}
	return (words);
}

static int	get_word_size(char *s, char c)
{
	int	size;

	size = 0;
	if (c == '\'' || c == '"')
		size++;
	while (s[size] && s[size] != c)
		size++;
	if (s[size] == '\'' || s[size] == '"')
		size++;
	return (size);
}

static char	lexer_fill_split(t_lexer *lexer, char *s)
{
	size_t	word;
	int		word_size;
	int		letter;

	word = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		if (!*s)
			break;
		if (*s == '"' || *s == '\'')
			word_size = get_word_size(s, *s);
		else
			word_size = get_word_size(s, ' ');
		lexer->split[word] = ft_calloc(word_size + 1, sizeof(char));
		if (!lexer->split[word])
			return (FALSE);
		letter = -1;
		while (++letter < word_size)
			lexer->split[word][letter] = *s++;
		word++;
	}
	return (TRUE);
}

char	**lexer_split(t_lexer *lexer, const char *input)
{
	size_t	split_counter;

	split_counter = lexer_count_words(input);
	if (!split_counter)
		return (FALSE);
	lexer->split = ft_calloc(split_counter + 1, sizeof(char *));
	if (!lexer->split)
		return (FALSE);
	if (lexer_fill_split(lexer, (char *)input))
		return (lexer->split);
	ft_split_free(lexer->split);
	return (FALSE);
}
