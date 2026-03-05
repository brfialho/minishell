/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:05:13 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 23:11:26 by brfialho         ###   ########.fr       */
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
void	mark_protected_quotes(char *s);
char	*trim_quotes(char *old_str);
char	**expand_argv(char **old_argv);
char	*expand_redir(char	*old_str);
char	**split_unprotected_spaces(char *s, char c);

#endif