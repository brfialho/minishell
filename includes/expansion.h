/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:05:13 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 21:40:50 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "libft.h"
#include "utils.h"

typedef struct s_expd
{
	char	*start;
	char	*env_key;
	char	*env_value;
}	t_expd;


void	del_exp_var(void *content);
char	*expand_string(char *old_str);
char	**expand_argv(char **old_argv);
char	**split_unprotected_spaces(char *s, char c);

#endif