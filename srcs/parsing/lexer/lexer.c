/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:57:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/28 22:10:00 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*alloc_token(t_token_code code, char *s)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->code = code;
	token->string = s;
	return (token);
}

t_state	get_state(char c)
{
	if (!c)
		return (IN_NULL);
	if (c == '"')
		return (IN_D_QUOTES);
	if (c == '\'')
		return (IN_S_QUOTES);
	if (c == ' ')
		return (IN_SPACE);
	if (ft_str_charcount(OPERATOR, c))
		return (IN_OPERATOR);
	return (DEFAULT);
}

char	*tokenize_operator(t_lexer *lexer, char *input)
{
	t_token *token;
	int		i;

	i = 0;
	while (ft_strncmp(input, lexer->op_lst[i].str, lexer->op_lst[i].str_len))
		i++;
	token = alloc_token(lexer->op_lst[i].code, lexer->op_lst[i].str);
	if (!token)
		lexer->error = TRUE;
	lst_add_end(lexer->token_lst, lst_new_node(token));
	return (input + lexer->op_lst[i].str_len);
}

char	*tokenize_default(t_lexer *lexer, char *input)
{
	int		len;
	char	*token_str;
	t_token	*token;

	len = 0;
	while(get_state(input[len]) == DEFAULT)
		len++;
	token_str = ft_calloc(len + 1, sizeof(char));
	if (!token_str)
		lexer->error = TRUE;
	ft_memcpy(token_str, input, len);
	if (!token_str)
		lexer->error = TRUE;
	token = alloc_token(WORD, token_str);
	if (!token)
		lexer->error = TRUE;
	lst_add_end(lexer->token_lst, lst_new_node(token));
	return (input + len);
}

char	*tokenize_quoted(t_lexer *lexer, char *input)
{
	t_token	*token;
	char	*token_str;
	int		len;

	len = 1;
	while (input[len] && get_state(input[len]) != lexer->state)
		len++;
	if (!input[len])
	{
		lexer->error = TRUE;
		return (input + len);
	}
	len++;
	token_str = ft_calloc(len + 1, sizeof(char));
	if (!token_str)
		lexer->error = TRUE;
	ft_memcpy(token_str, input, len);
	token = ft_calloc(1, sizeof(t_token));
	if (!token_str)
		lexer->error = TRUE;
	token = alloc_token(WORD, token_str);
	if (!token)
		lexer->error = TRUE;
	lst_add_end(lexer->token_lst, lst_new_node(token));
	return (input + len);
}

char	*tokenize(t_lexer *lexer, char *input)
{
	lexer->state = get_state(*input);
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

void	init_operators(t_lexer *lexer)
{
	lexer->op_lst[0] = (t_operator){"<<", 2, HEREDOC};
	lexer->op_lst[1] = (t_operator){">>", 2, APPEND};
	lexer->op_lst[2] = (t_operator){"&&", 2, LOGICAL_AND};
	lexer->op_lst[3] = (t_operator){"||", 2, LOGICAL_OR};
	lexer->op_lst[4] = (t_operator){"<", 1, INFILE};
	lexer->op_lst[5] = (t_operator){">", 1, OUTFILE};
	lexer->op_lst[6] = (t_operator){"&", 1, INVALID};
	lexer->op_lst[7] = (t_operator){"|", 1, PIPE};
	lexer->op_lst[8] = (t_operator){";", 1, INVALID};
	lexer->op_lst[9] = (t_operator){"=", 1, ASSIGNMENT};
	lexer->op_lst[10] = (t_operator){"(", 1, OPEN_PARENTHESIS};
	lexer->op_lst[11] = (t_operator){")", 1, CLOSE_PARENTHESIS};
	lexer->op_lst[12] = (t_operator){"\n", 1, ENDLINE};
}

void	lexer(t_lexer *lexer, const char *input)
{
	char	*s;

	lexer->token_lst = ft_calloc(1, sizeof(t_list **));
	if (!lexer->token_lst)
		return ;
	init_operators(lexer);
	s = (char *)input;
	while (*s)
	{
		while (*s == ' ')
			s++;
		s = tokenize(lexer, s);
	}
}
