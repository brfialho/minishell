/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:24:49 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 14:52:58 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "libft.h"
# include "utils.h"



typedef enum e_token_code
{
	INVALID,
	WORD,
	LOGICAL_AND,
	LOGICAL_OR,
	PIPE,
	ASSIGNMENT,
	INFILE,
	OUTFILE,
	APPEND,
	HEREDOC,
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
	char			precedence;
}	t_token;

typedef struct s_operator
{
	char			precedence;
	char			*str;
	int				str_len;
	t_token_code 	code;
}	t_operator;

typedef struct s_lexer
{
	t_state		state;
	t_list		**token_lst;
	t_operator	op_lst[OP_COUNT];
	int			error;
}	t_lexer;

void	ft_lexer(t_lexer *lexer, const char *input);
char	*tokenize(t_lexer *lexer, char *input);
void	lexer_destroy(t_lexer *lexer);

# endif
