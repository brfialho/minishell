/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:05:13 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/06 23:49:16 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "libft.h"
#include "defines.h"

typedef struct s_expd
{
	char	*start;
	char	*env_key;
	char	*env_value;
}	t_expd;

typedef struct s_redir t_redir;
typedef struct s_env t_env;

void	del_exp_var(void *content);
char	*expand_string(char *old_str, t_bool heredoc, t_env **env);
void	mark_protected_quotes(char *s);
char	*trim_quotes(char *old_str);
char	**expand_argv(char **old_argv, t_env **env);
void	expand_heredoc(t_redir *redir, t_env **env);
t_bool	expand_redir(t_redir *redir, t_env **env);
t_bool	expand_all_redir(t_list **redir_lst, t_env **env);
char	**split_unprotected_spaces(char *s, char c);

#endif