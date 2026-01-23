/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:57:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/23 19:39:20 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	lexer_count_words(char const *s)
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

char	in_word(t_lexer *lexer, char *s, int i)
{
	int	bool;
	
	if ((lexer->state == IN_D_QUOTES && s[i - 1] == '"') 
		|| ((lexer->state = IN_S_QUOTES) && s[i - 1] == '\''))
			lexer->state = DEFAULT;
	bool = s[i] 
			&& ((s[i] != ' ' && lexer->state == DEFAULT)
			|| (s[i] != '"' && lexer->state == IN_D_QUOTES)
			|| (s[i] != '\'' && lexer->state == IN_S_QUOTES));
	if (s[i] == '"' && lexer->state == DEFAULT)
			lexer->state = IN_D_QUOTES;
	if (s[i] == '\'' && lexer->state == DEFAULT)
			lexer->state = IN_S_QUOTES;
	return (bool);
}

char	lexer_fill_split(t_lexer *lexer, char *s)
{
	size_t	word;
	int		letter;

	word = 0;
	while (*s && *s == ' ')
		s++;
	while (*s)
	{
		letter = 0;
		while (in_word(lexer, s, letter))
			letter++;
		lexer->split[word] = ft_calloc(letter + 1, sizeof(char));
		if (!lexer->split[word])
			return (0);
		letter = -1;
		while (in_word(lexer, s, ++letter))
			lexer->split[word][letter] = s[letter];
		word++;
		letter = 0;
		while (s[letter] && s[letter] == ' ')
			letter++;
		s += letter;
	}
	return (1);
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

void	lexer(t_list **head, const char *input)
{
	t_lexer	lexer;

	lexer.state = DEFAULT;
	lexer_split(&lexer, input);

	(void)head;
	ft_printf("%d\n", lexer_count_words(input));
	int	i;

	i = 0;
	while (lexer.split[i])
		ft_printf("ITEM: %s\n", lexer.split[i++]);
}