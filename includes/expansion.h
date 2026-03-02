/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:05:13 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/02 16:13:47 by brfialho         ###   ########.fr       */
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
void	fill_expd_str(char	*old, char *new, t_list *expd_var_lst);
char	*expand_string(char *old_str);
char	**expand_argv(char **old_argv);

#endif