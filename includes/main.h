/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:24:10 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/22 02:56:10 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "parser.h"
# include "execution.h"
# include "handler.h"
# include "set_signal.h"

typedef struct s_mini
{
	char	*input;
	t_lexer	lexer;
	t_ast	**root;
}	t_mini;

void	parsing(t_mini *mini);
void	executor(t_mini *mini);

extern int g_status_shell;

#endif
