/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:48:16 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/13 21:26:12 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

// Utils
# define STDIN 0
# define STDOUT 1
# define STDERR 2

// Colours
# define RED "\001\033[31m\002"
# define BOLD_RED "\001\033[1;31m\002"
# define GREEN "\001\033[32m\002"
# define ORANGE "\001\033[38;5;208m\002"
# define YELLOW_ORANGE "\001\033[38;5;214m\002"
# define LIGHT_ORANGE "\001\033[38;5;214m\002"
# define BRIGHT_RED "\001\033[91m\002"
# define DARK_RED "\001\033[38;5;124m\002"
# define BRIGHT_YELLOW "\001\033[38;5;226m\002"
# define GOLD "\001\033[38;5;220m\002"
# define BOLD "\001\033[1m\002"
# define RESET "\001\033[0m\002"
# define YELLOW "\001\033[33m\002"

// Lexer
// && operator has to be treated specially since & is a normal char
# define OPERATOR "|<>" 
# define WHITESPACE " \t"
# define OP_COUNT 7

// Signal
# define EXIT_CODE 130

// Readlines
// # define PROMPT_START RED BOLD "🔥Minihell🔥 " RESET
// # define PROMPT_END "$ " RESET
# define PRMPT_STRT "\001\033[31m\002\001\033[1m\002🔥Minihell🔥 \001\033[0m\002"
# define PROMPT_END "$ \001\033[0m\002"

// Error Messages
# define QUOTE_ERROR "Minishell: unexpected EOF while looking for matching"
# define SYNTAX_ERROR "Minishell: syntax error near unexpected token"
# define REDIR_IN_ERROR "Minishell: '%s': No such file or directory\n"

// Expansion
# define ARGV_EXPAND_DELIMITER " $-'\"\x01\x02\n"
# define EXPAND_SPECIAL "$?"
# define S_QUOTE '\x02'
# define D_QUOTE '\x01'

#endif