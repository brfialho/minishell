/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:29:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/21 20:41:14 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define META "|&;()<>\n\t "

typedef enum e_token_code
{
	WORD,
	PIPE,
	AND,
	OR,
	INFILE,
	OUTFILE,
	APPEND,
	NEWLINE,
	HEARDOC
}	t_token_code;

typedef struct s_token
{
	t_token_code	code;
	char			*string;
}	t_token;

void	tokenizer(t_list **head, char *input);

#endif