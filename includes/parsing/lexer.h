/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:24:49 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/24 03:13:02 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "libft.h"
# include "utils.h"

typedef enum e_token_code
{
	INVALID,
	INFILE,
	OUTFILE,
	APPEND,
	HEREDOC,
	WORD,
	QUOTED_WORD,
	LOGICAL_AND,
	LOGICAL_OR,
	PIPE,
	ASSIGNMENT,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	EXPANSION
}	t_token_code;

typedef enum e_state
{
	DEFAULT,
	IN_OPERATOR,
	IN_D_QUOTES,
	IN_S_QUOTES,
	IN_SPACE,
	IN_NULL
}	t_state;

typedef struct s_token
{
	t_token_code	code;
	char			*string;
	t_int8			precedence;
	t_bool			expandable;
	t_bool 			space_next;
}	t_token;

typedef struct s_operator
{
	t_int8			precedence;
	char			*str;
	int				str_len;
	t_token_code 	code;
}	t_operator;

typedef struct s_lexer
{
	t_state		state;
	t_list		**token_lst;
	t_operator	op_lst[OP_COUNT];
	char		*unclosed_quotes;
}	t_lexer;

t_bool	ft_lexer(t_lexer *lexer, const char *input);
char	*tokenize(t_lexer *lexer, char *input);
void	trim_quoted_tokens(t_lexer *lexer);
void	lexer_destroy(t_lexer *lexer);
void	lexer_quotes_error(t_lexer *lexer, const char *input);

# endif
