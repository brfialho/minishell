/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:30:38 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 13:56:18 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "main.h"
# include "builtins.h"
# include "handler.h"
# include "set_signals.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_cmd
{
	char	**argv;
	char	*path;
	t_redir	*redir;
	int		heredoc_fd;
	struct	s_cmd *next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

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