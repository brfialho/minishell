/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:41:13 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 03:05:24 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "main.h"

# define TEST BOLD "%d. " RESET "Testing with " YELLOW BOLD "\"%s\"\n"
# define SUCCESS GREEN BOLD "=== SUCCESS ✅ ===\n\n" RESET
# define FAIL RED BOLD "=== FAILURE ❌ ===\n\n" RESET

#endif