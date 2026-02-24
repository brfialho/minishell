/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:29:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 04:54:44 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lexer.h"
# include "utils.h"

typedef enum e_node_type
{
	NODE_EXEC = 1,
	NODE_PIPE = 2,
	NODE_OR = 3,
	NODE_AND = 4,
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN = 5,
	REDIR_OUT = 6,
	REDIR_APPEND = 7,
	REDIR_HEREDOC = 8,
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
	// t_expand	expand[100];
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