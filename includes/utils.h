/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:48:16 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/05 15:38:22 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
 #define UTILS_H

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
# define GREEN "\001\033[32m\002"
# define BOLD "\001\033[1m\002"
# define RESET "\001\033[0m\002"
# define YELLOW "\001\033[33m\002"

// Lexer
# define OPERATOR "|<>" // && operator has to be treated specially since & is a normal char
# define WHITESPACE " \t"
# define OP_COUNT 7

// Signal
# define EXIT_CODE 130

// Readlines
# define PROMPT "\001\033[31m\033[1m\002🔥Minihell\001\033[0m\033[1m🔥 \033[0m\002"

// Error Messages
# define QUOTE_ERROR "Minishell: unexpected EOF while looking for matching"
# define SYNTAX_ERROR "Minishell: syntax error near unexpected token"

#endif