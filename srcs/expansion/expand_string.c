/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:09:39 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/02 20:46:22 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static t_list	**get_exp_var_lst(char *s);
static char	*set_new_expd_var_info(char	*s, t_list **expd_var_lst);
static int	get_expanded_len(char *s, t_list *expd_var_lst);
static char	*trim_quotes(char *old_str);

char	*expand_string(char *old_str)
{
	t_list	**expd_var_lst;
	char	*expd_str;

	if (!ft_str_charcount(old_str, '$'))
		return (old_str);
	expd_var_lst = get_exp_var_lst(old_str);
	expd_str = ft_safe_calloc(get_expanded_len(old_str, *expd_var_lst) + 1, sizeof(char));
	fill_expd_str(old_str, expd_str, *expd_var_lst);
	expd_str = trim_quotes(expd_str);

	// ft_printf("\nBEFORE: %s\n", old_str);
	// ft_printf("AFTER : %s\n", expd_str);
	
	lst_del_all(expd_var_lst, del_exp_var);
	free(old_str);
	free (expd_var_lst);
	return (expd_str);
}

static t_list	**get_exp_var_lst(char *s)
{
	char	state;
	t_list 	**expd_var_lst;

	expd_var_lst = ft_safe_calloc(1, sizeof(t_list *));
	state = 0;
	while (*s)
	{
		if (state && state == *s)
			state = 0;
		else if (state == 0 && (*s == '\'' || *s == '"'))
			state = *s;
		if (*s == '$' && *(s + 1) && state < '\'')
			s = set_new_expd_var_info(s + 1, expd_var_lst);
		s++;
	}
	return (expd_var_lst);
}

static char	*set_new_expd_var_info(char	*s, t_list **expd_var_lst)
{
	if (ft_str_charcount(EXPAND_SPECIAL, *s))
		return (s); // DO SOMETHING

	t_expd	*content;
	int		len;

	content = ft_safe_calloc(1, sizeof(t_expd));
	len = 0;
	content->start = s;
	while (s[len] && !ft_str_charcount(EXPAND_DELIMITER, s[len]))
		len++;
	content->env_key = ft_substr(s, 0, len);
	content->env_value = getenv(content->env_key);
	s += len - 1;
	lst_add_end(expd_var_lst, lst_new_node(content));
	return (s);
}

static int	get_expanded_len(char *s, t_list *expd_var_lst)
{
	t_list	*lst;
	int		len;

	len = ft_strlen(s);
	lst = expd_var_lst;
	while (lst)
	{
		len += ft_strlen(((t_expd *)lst->content)->env_value);
		lst = lst->next;
	}
	return (len);
}

static char	*trim_quotes(char *old_str)
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
		else if (state == 0 && (*old == '\'' || *old == '"'))
			state = *old++;
		else 
			*new++ = *old++;
	}
	free (old_str);
	return (new_str);
}
