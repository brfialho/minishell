/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:30:38 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 20:40:07 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "utils.h"
# include "builtins.h"
# include "handler.h"

int			ft_exec_cmd(t_cmd *cmd, t_env **envp);
int 		prepare_heredocs(t_n_redir *redir, t_cmd *cmd);
int 		apply_redirections(t_n_redir *redir, t_cmd *cmd);
int			open_redir_fd(t_n_redir *redir);
int			apply_redir_fd(int fd, t_n_redir *redir);
int			solve_heredoc(t_n_redir *redir, t_cmd *cmd);
int			read_heredoc_loop(t_n_redir *redir, int write_fd);
int     	is_builtin(char *cmd);
int			execute_builtin(t_cmd *cmd, t_env **env);
int			exec_builtin_parent(t_cmd *cmd, t_env **env);
int			exec_pipeline_ast(t_ast *node, t_env **env);
int			exec_pipeline_list(t_cmd *cmd, t_env **env);
int 		exec_node(t_ast *node, t_env **env);	
int 		exec_single_ast(t_ast *node, t_env **env);
t_cmd		*convert_ast_pipeline(t_ast *node);
t_cmd		*cmd_add_back(t_cmd *left, t_cmd *right);
t_cmd	    *create_cmd_from_ast(t_ast *node);
t_n_redir 	*new_exec_redir(t_redir *ast_redir);
t_n_redir 	*convert_redir_list(t_list *ast_list);
void		exec_builtin_child(t_cmd *cmd, t_env **env);
void		ft_cleaner_list(t_cmd *list);
void 		free_exec_redir_list(t_n_redir *redir);
void		ft_free_matrix(char ***matrix);
char    	*read_prompt_line(void);
char		*get_path_dirs(t_cmd *cmd, t_env **envp);
char 		*get_env_value(t_env *env, char *key);

#endif