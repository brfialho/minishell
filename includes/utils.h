/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:48:16 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/22 03:28:34 by brfialho         ###   ########.fr       */
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

// Lexer
# define OPERATOR "|&;()<>="
# define WHITESPACE " \t"
# define OP_COUNT 12

// Signal
# define EXIT_CODE 130

// Readlines
# define PROMPT "\033[31m\033[1mMinihell\033[0m\033[1m$ \033[0m"

#endif