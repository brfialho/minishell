/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:00:28 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/21 22:25:00 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"
# include "parser.h"

typedef struct s_n_redir t_n_redir;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	t_n_redir		*redir;
	int				heredoc_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_n_redir
{
	int					type;
	char				*target;
	struct s_n_redir	*next;
}	t_n_redir;

int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_cmd *cmd, t_env **env);
int		builtin_pwd(void);
int		builtin_export(t_cmd *cmd, t_env **env);
int		builtin_unset(t_cmd *cmd, t_env **env);
int		builtin_env(t_env *envp);
int		builtin_exit(void);
int		env_len(t_env *env);
char	*ft_get_envp(t_env *env, char *key);
char	**env_to_envp(t_env *env);
t_env	*env_new(char *key, char *value);
t_env	*env_from_envp(char **envp);
void	env_add_back(t_env **env, t_env *new);
void	ft_set_env(t_env **env, char *key, char *value);
void	ft_unset_env(t_env **env, char *key);
void	free_envp(char **envp);

#endif