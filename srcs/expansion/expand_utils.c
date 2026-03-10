/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:10:06 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 08:45:00 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	del_exp_var(void *content)
{
	t_expd	*exp;

	exp = content;
	free (exp->env_key);
	free(exp->env_value);
	free(exp);
}

void	mark_protected_quotes(char *s)
{
	char	state;

	state = 0;
	while (*s)
	{
		if (state && *s == state)
		{
			*s = (state == '\'') * S_QUOTE + (state == '"') * D_QUOTE;
			state = 0;
		}
		else if (state == 0 && (*s == '\'' || *s == '"'))
		{
			state = *s;
			*s = (state == '\'') * S_QUOTE + (state == '"') * D_QUOTE;
		}
		s++;
	}
}

char	*trim_quotes(char *old_str)
{
	char	*new_str;
	char	*new;
	char	*old;
	char	state;

	new_str = ft_safe_calloc(ft_strlen(old_str) + 1, sizeof(char));
	new = new_str;
	old = old_str;
	state = 0;
	while (*old)
	{
		if (state && state == *old)
		{
			state = 0;
			old++;
		}
		else if (state == 0 && (*old == S_QUOTE || *old == D_QUOTE))
			state = *old++;
		else
			*new++ = *old++;
	}
	free (old_str);
	return (new_str);
}
