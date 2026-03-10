/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:30:38 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 19:13:26 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "defines.h"
# include "builtins.h"

int			ft_exec_cmd(t_cmd *cmd, t_env **envp, t_mini *mini);
int 		apply_redirections(t_n_redir *redir, t_cmd *cmd);
int			open_redir_fd(t_n_redir *redir);
int			apply_redir_fd(int fd, t_n_redir *redir);
int			is_builtin(char *cmd);
int			execute_builtin(t_cmd *cmd, t_env **env, int is_parent, t_mini *mini);
int			exec_builtin_parent(t_cmd *cmd, t_env **env, t_mini *mini);
int			exec_pipeline_ast(t_ast *node, t_env **env, t_mini *mini);
int			exec_pipeline_list(t_cmd *cmd, t_env **env, t_mini *mini);
int 		exec_node(t_ast *node, t_env **env, t_mini *mini);	
int			setup_pipe_if_needed(int *pipe_fd, t_cmd *cmd);
int 		exec_single_ast(t_ast *node, t_env **env, t_mini *mini);
int			wait_for_last_pid(pid_t last_pid);
int			extract_exit_status(int status);
int 		setup_heredoc_to_stdin(char *heredoc_string);
t_cmd		*convert_ast_pipeline(t_ast *node, t_env **env);
t_cmd		*cmd_add_back(t_cmd *left, t_cmd *right);
t_cmd		*create_cmd_from_ast(t_ast *node, t_env **env);
t_n_redir 	*new_exec_redir(t_redir *ast_redir);
t_n_redir 	*convert_redir_list(t_list *ast_list);
void		exec_child(t_cmd *cmd, t_env **env, t_mini *mini);
void		exec_builtin_child(t_cmd *cmd, t_env **env, t_mini *mini);
void		ft_cleaner_list(t_cmd *list);
void		resolve_pipeline_paths(t_cmd *cmd, t_env **env);
void 		free_exec_redir_list(t_n_redir *redir);
void		ft_free_matrix(char ***matrix);
void		cleanup_pipe_on_fork_error(int *pipe_fd, t_cmd *cmd);
void		update_prev_fd(int *prev_fd, int *pipe_fd, t_cmd *cmd);
void		destroy_exec_cmd(t_cmd *cmd);
void		cleanup_exit(t_cmd *cmd, t_mini *mini);
void 		executor(t_mini *mini);
char		*read_prompt_line(void);
char		*get_path_dirs(t_cmd *cmd, t_env **envp);
char		*get_env_value(t_env *env, char *key);

#endif