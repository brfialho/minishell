/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:24:10 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/26 22:15:57 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "parser.h"
# include "execution.h"
# include "handler.h"
# include "set_signal.h"
# include "error.h"

typedef enum e_error
{
	NO_ERROR = 0,
	UNCLOSED_QUOTES = 1,
	SYNTAX = 2,
	OTHER = 10,
}	t_error;

typedef struct s_mini
{
	char	*input;
	t_lexer	lexer;
	t_ast	**root;
	t_error error_code;
}	t_mini;

t_bool	parsing(t_mini *mini);
void	executor(t_mini *mini);

extern int g_status_shell;

#endif
