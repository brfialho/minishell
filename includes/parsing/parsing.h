/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:29:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/23 18:07:11 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define META "|&;()<>\n\t"

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
	IN_D_QUOTES,
	IN_S_QUOTES
}	t_state;

typedef struct s_token
{
	t_token_code	code;
	char			*string;
}	t_token;

typedef struct s_lexer
{
	t_state	state;
	t_token	*token;
	char	**split;
}	t_lexer;


void	lexer(t_list **head, const char *input);

#endif