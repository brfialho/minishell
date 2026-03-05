/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:10:06 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 21:40:18 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	del_exp_var(void *content)
{
	t_expd	*exp;

	exp = content;
	free (exp->env_key);
	free(exp);
}
