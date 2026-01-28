/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:29:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/28 18:43:40 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define OPERATOR "|&;()<>"

typedef enum e_token_code
{
	WORD,
	AND,
	OR,
	APPEND,
	HEARDOC,
	PIPE,
	INFILE,
	OUTFILE
}	t_token_code;

typedef enum e_state
{
	DEFAULT,
	IN_OPERATOR,
	IN_D_QUOTES,
	IN_S_QUOTES,
	IN_NULL
}	t_state;

typedef struct s_token
{
	t_token_code	code;
	char			*string;
}	t_token;

typedef struct s_lexer
{
	t_state	state;
	t_list	**token_lst;
	char	**split;
	int		error;
}	t_lexer;


void	lexer(t_lexer *lexer, const char *input);
char	**lexer_split(t_lexer *lexer, const char *input);

#endif