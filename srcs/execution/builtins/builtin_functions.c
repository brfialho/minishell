/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:30:44 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 15:01:44 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_cd(t_cmd *cmd, t_env **env)
{
	char	*path;
	char	*oldpwd;
	char	*cwd;

	oldpwd = ft_get_envp(*env, "PWD");
	if (!cmd->argv[1])
		path = ft_get_envp(*env, "HOME");
	else
		path = cmd->argv[1];
	if (!path)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		if (oldpwd)
			ft_set_env(env, "OLDPWD", oldpwd);
		ft_set_env(env, "PWD", cwd);
		free(cwd);
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*eq;

	if (!cmd->argv[1])
		return (0);
		// return (env_print_sorted(*env), 0);
	i = 1;
	while (cmd->argv[i])
	{
		eq = ft_strchr(cmd->argv[i], '=');
		if (eq)
		{
			*eq = '\0';
			ft_set_env(env, cmd->argv[i], eq + 1);
			*eq = '=';
		}
		else
			ft_set_env(env, cmd->argv[i], NULL);
		i++;
	}
	return (0);
}

int	builtin_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		ft_unset_env(env, cmd->argv[i]);
		i++;
	}
	return (0);
}
