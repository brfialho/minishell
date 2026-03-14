/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:09:39 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/13 21:44:51 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "builtins.h"
#include "main.h"

static t_list	**get_exp_var_lst(char *s, t_bool heredoc, t_env **env);
static char		*set_new_expd_var_info(char	*s, t_list **expd_var_lst,
					t_env **env);
static int		get_expanded_len(char *s, t_list *expd_var_lst);
static void		fill_expd_str(char	*old, char *new, t_list *expd_var_lst);

char	*expand_string(char *old_str, t_bool heredoc, t_env **env)
{
	t_list	**expd_var_lst;
	char	*expd_str;

	if (!ft_str_charcount(old_str, '$'))
		return (old_str);
	expd_var_lst = get_exp_var_lst(old_str, heredoc, env);
	expd_str = ft_safe_calloc(
			get_expanded_len(old_str, *expd_var_lst) + 1, sizeof(char));
	fill_expd_str(old_str, expd_str, *expd_var_lst);
	lst_del_all(expd_var_lst, del_exp_var);
	free(old_str);
	free (expd_var_lst);
	return (expd_str);
}

static t_list	**get_exp_var_lst(char *s, t_bool heredoc, t_env **env)
{
	char	state;
	t_list	**expd_var_lst;

	expd_var_lst = ft_safe_calloc(1, sizeof(t_list *));
	state = 0;
	while (*s)
	{
		if (state && state == *s)
			state = 0;
		else if (state == 0 && (*s == S_QUOTE || *s == D_QUOTE))
			state = *s;
		if (*s == '$' && *(s + 1)
			&& !ft_str_charcount(ARGV_EXPAND_DELIMITER, *(s + 1))
			&& ((!heredoc && state != S_QUOTE) || heredoc))
			s = set_new_expd_var_info(s + 1, expd_var_lst, env);
		s++;
	}
	return (expd_var_lst);
}

static char	*set_new_expd_var_info(char	*s, t_list **expd_var_lst, t_env **env)
{
	t_expd	*content;
	int		len;

	if (*s == '$')
		return (s);
	content = ft_safe_calloc(1, sizeof(t_expd));
	len = 0;
	content->start = s;
	while (s[len] && !ft_str_charcount(ARGV_EXPAND_DELIMITER, s[len]))
		len++;
	content->env_key = ft_substr(s, 0, len);
	content->env_value = ft_get_envp(*env, content->env_key);
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

static void	fill_expd_str(char	*old, char *new, t_list *expd_var_lst)
{
	t_list	*lst;
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
