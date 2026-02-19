/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:30:38 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 16:51:40 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "utils.h"
# include "builtins.h"
# include "handler.h"

int		ft_exec_cmd(t_cmd *cmd, t_env **envp);
int		set_redir(t_redir *redir, t_cmd *cmd);
int		open_redir_fd(t_redir *redir);
int		apply_redir_fd(int fd, t_redir *redir);
int		solve_heredoc(t_redir *redir, t_cmd *cmd);
int		read_heredoc_loop(t_redir *redir, int write_fd);
int     is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_env **env);
int		exec_builtin_parent(t_cmd *cmd, t_env **env);
int		exec_pipeline_ast(t_ast *node, t_env **env);
int 	exec_node(t_ast *node, t_env **env);
int 	exec_single_ast(t_ast *node, t_env **env);
t_cmd	*convert_ast_pipeline(t_ast *node);
t_cmd	*cmd_add_back(t_cmd *left, t_cmd *right);
void	exec_builtin_child(t_cmd *cmd, t_env **env);
void	ft_cleaner_list(t_cmd *list);
char    *read_prompt_line(void);

#endif