/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:10:06 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/02 16:13:06 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	fill_expd_str(char	*old, char *new, t_list *expd_var_lst)
{
	t_list *lst;
	char	*s;

	lst = expd_var_lst;
	while (*old)
	{
		if (lst && old && old + 1 == ((t_expd *)lst->content)->start)
		{
			s = ((t_expd *)lst->content)->env_value;
			while (s && *s)
				*new++ = *s++;
			old += ft_strlen(((t_expd *)lst->content)->env_key);
			new--;
			lst = lst->next;
		}
		else
			*new = *old;
		new++;
		old++;
	}
}

void	del_exp_var(void *content)
{
	t_expd	*exp;

	exp = content;
	free (exp->env_key);
	free(exp);
}
