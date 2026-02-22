/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:29:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/22 03:20:54 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lexer.h"
# include "utils.h"

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

typedef struct s_expand
{
	char	expandable;
	int		len;
}	t_expand;

typedef struct s_msh_ast
{
	t_node_type	type;
	t_list		**redir;
	char		**argv;
	t_expand	expand[100];
	char		*path;
	char		*str;
}	t_msh_ast;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
}	t_redir;

void	parser(t_ast ***root, t_lexer *lexer);
t_ast	*ast_builder(t_list *token_lst);
t_ast	*get_operator_node(t_token *token);
t_ast	*get_exec_node(t_list *token_lst);
void	parser_destroy(t_ast **root);

#endif