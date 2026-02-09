/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:00:28 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/09 10:13:52 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parsing/parsing.h"
# include "execution/execution.h"
# include "main.h"

int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_cmd *cmd, t_env **env);
int		builtin_pwd(void);
int		builtin_export(t_cmd *cmd, t_env **env);
int		builtin_unset(t_cmd *cmd, t_env **env);
int		builtin_env(t_env *envp);
int		builtin_exit(t_cmd *cmd);
int     env_len(t_env *env);
char	*ft_get_envp(t_env *env, char *key);
char	**env_to_envp(t_env *env);
t_env	*env_new(char *key, char *value);
t_env	*env_from_envp(char **envp);
void	env_add_back(t_env **env, t_env *new);
void	ft_set_env(t_env **env, char *key, char *value);
void	ft_unset_env(t_env **env, char *key);
void	free_envp(char **envp);
 
#endif