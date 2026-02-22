/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:41:13 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/21 19:54:12 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "main.h"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define BOLD "\033[1m"
# define RESET "\033[0m"
# define YELLOW "\033[33m"

# define TEST BOLD "%d. " RESET "Testing with " YELLOW BOLD "\"%s\"\n"
# define SUCCESS GREEN BOLD "=== SUCCESS ✅ ===\n\n" RESET
# define FAIL RED BOLD "=== FAILURE ❌ ===\n\n" RESET

#endif