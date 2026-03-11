/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:24:10 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/11 19:31:55 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "parser.h"
# include "execution.h"
# include "shell_signal.h"
# include "error.h"
# include "expansion.h"

typedef enum e_error
{
	NO_ERROR = 0,
	UNCLOSED_QUOTES = 1,
	SYNTAX = 2,
	HEREDOC_SIGINT = 3,
	OTHER = 10,
}	t_error;

typedef struct s_mini
{
	char	*input;
	int		prompt_len;
	t_lexer	lexer;
	t_ast	**root;
	t_error	error_code;
	t_env	*env;
	int		exit_status;
}	t_mini;

char	*read_prompt_line(t_mini *mini);
t_error	collect_heredocs(t_mini *mini);
t_bool	process_input_pipeline(t_mini *mini);
void	executor(t_mini *mini);

extern int	g_shell_signal;

#endif
