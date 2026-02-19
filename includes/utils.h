/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:48:16 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 18:00:46 by brfialho         ###   ########.fr       */
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
# define OPERATOR "|&;()<>=$"
# define OP_COUNT 13

// Signal
# define EXIT_CODE 130

void	*safe_calloc(size_t nmemb, size_t size);

#endif