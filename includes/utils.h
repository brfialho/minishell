/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:48:16 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 03:10:49 by brfialho         ###   ########.fr       */
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
# define RED "\033[31m"
# define GREEN "\033[32m"
# define BOLD "\033[1m"
# define RESET "\033[0m"
# define YELLOW "\033[33m"

// Lexer
# define OPERATOR "|<>" // && operator has to be treated specially since & is a normal char
# define WHITESPACE " \t"
# define OP_COUNT 7

// Signal
# define EXIT_CODE 130

// Readlines
# define PROMPT "\033[31m\033[1m🔥Minihell\033[0m\033[1m🔥 \033[0m"

// Error Messages
# define QUOTE_ERROR "Minishell: unexpected EOF while looking for matching"

#endif