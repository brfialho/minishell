/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:24:10 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 13:56:42 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "parsing.h"
# include "execution.h"
# include "handler.h"
# include "set_signals.h"

extern int g_status_shell;

typedef enum e_node_type
{
	NODE_EXEC,
	NODE_PIPE,
	NODE_OR,
	NODE_AND,
	NODE_SUB
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN = 1,
	REDIR_OUT = 2,
	REDIR_APPEND = 3,
	REDIR_HEREDOC = 4,
}	t_redir_type;

typedef struct s_msh_ast
{
	t_node_type	type;
	t_list		**redir;
	char		**argv;
	char		*path;
	char		*str;
}	t_msh_ast;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
}	t_redir;

void	*safe_calloc(size_t nmemb, size_t size);

#endif
