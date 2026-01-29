/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:29:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/28 21:20:15 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define OPERATOR "|&;()<>="

# define OP_COUNT 13

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
	ENDLINE
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
}	t_token;

typedef struct s_operator
{
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

	char		**split;
}	t_lexer;


void	lexer(t_lexer *lexer, const char *input);
char	**lexer_split(t_lexer *lexer, const char *input);

#endif