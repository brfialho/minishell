/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:29:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/23 17:22:33 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define META "|&;()<>\n\t"

typedef enum e_token_code
{
	WORD = 0,
	AND = 1,
	OR = 2,
	APPEND = 3,
	HEARDOC = 4,
	PIPE = '|',
	INFILE = '<',
	OUTFILE = '>'
}	t_token_code;

typedef struct s_token
{
	t_token_code	code;
	char			*string;
}	t_token;

typedef struct s_lexer
{
	t_token	*token;
	char	*left;
	int		state;
}	t_lexer;


void	lexer(t_list **head, const char *input);

#endif