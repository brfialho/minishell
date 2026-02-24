/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:31:09 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 02:30:16 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_state	get_state(char *s);
static char	*tokenize_operator(t_lexer *lexer, char *input);
static char	*tokenize_default(t_lexer *lexer, char *input);
static char	*tokenize_quoted(t_lexer *lexer, char *input);

char	*tokenize(t_lexer *lexer, char *input)
{
	lexer->state = get_state(input);
	if (lexer->state == IN_NULL)
		return (input);
	if (lexer->state == IN_D_QUOTES 
		|| lexer->state == IN_S_QUOTES)
		return (tokenize_quoted(lexer, input));
	if (lexer->state == IN_OPERATOR)
		return (tokenize_operator(lexer, input));
	else
		return (tokenize_default(lexer, input));
}

static char	*tokenize_quoted(t_lexer *lexer, char *input)
{
	t_token	*token;
	char	*token_str;
	int		len;

	len = 1;
	while (input[len] && get_state(input + len) != lexer->state)
		len++;
	if (!input[len])
		return (lexer->unclosed_quotes = input, input + len);
	len++;
	token_str = ft_safe_calloc(len + 1, sizeof(char));
	ft_memcpy(token_str, input, len);
	token = ft_safe_calloc(1, sizeof(t_token));
	token->code = WORD;
	token->string = token_str;
	token->precedence = 0;
	if (ft_str_charcount(WHITESPACE, input[len]))
		token->space_next = TRUE;
	if (lexer->state == IN_D_QUOTES)
		token->expandable = TRUE;
	lst_add_end(lexer->token_lst, lst_new_node(token));
	return (input + len);
}

static char	*tokenize_default(t_lexer *lexer, char *input)
{
	int		len;
	char	*token_str;
	t_token	*token;

	len = 0;
	while(get_state(input + len) == DEFAULT)
		len++;
	token_str = ft_safe_calloc(len + 1, sizeof(char));
	ft_memcpy(token_str, input, len);
	token = ft_safe_calloc(1, sizeof(t_token));
	token->code = WORD;
	token->string = token_str;
	token->precedence = 0;
	token->expandable = TRUE;
	if (ft_str_charcount(WHITESPACE, input[len]))
		token->space_next = TRUE;
	lst_add_end(lexer->token_lst, lst_new_node(token));
	return (input + len);
}

static char	*tokenize_operator(t_lexer *lexer, char *input)
{
	t_token *token;
	int		i;

	i = 0;
	while (ft_strncmp(input, lexer->op_lst[i].str, lexer->op_lst[i].str_len))
		i++;
	token = ft_safe_calloc(1, sizeof(t_token));
	token->code = lexer->op_lst[i].code;
	token->string = lexer->op_lst[i].str;
	token->precedence = lexer->op_lst[i].precedence;
	lst_add_end(lexer->token_lst, lst_new_node(token));
	return (input + lexer->op_lst[i].str_len);
}

static t_state	get_state(char *s)
{
	if (!*s)
		return (IN_NULL);
	if (*s == '"')
		return (IN_D_QUOTES);
	if (*s == '\'')
		return (IN_S_QUOTES);
	if (*s == ' ')
		return (IN_SPACE);
	if (ft_str_charcount(OPERATOR, *s)
		|| !ft_strncmp ("&&", s, 2))
		return (IN_OPERATOR);
	return (DEFAULT);
}
