/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:29:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/27 22:52:18 by brfialho         ###   ########.fr       */
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
	NODE_PIPE = 6,
	NODE_AND = 7,
	NODE_OR = 8,
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN = 1,
	REDIR_OUT = 2,
	REDIR_APPEND = 3,
	REDIR_HEREDOC = 4,
	REDIR_HEREDOC_NO_EXPANSION = 5,
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

typedef struct s_mini t_mini;

t_int8	parser(t_ast ***root, t_lexer *lexer);
t_ast	*ast_builder(t_list *token_lst);
t_ast	*get_operator_node(t_token *token);
t_ast	*get_exec_node(t_list *token_lst);
t_int8	syntax_validator(t_ast *root);
void	parser_error_handler(t_mini *mini);
void	parser_destroy(t_ast **root);

#endif