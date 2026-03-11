/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 21:21:37 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 23:02:50 by brfialho         ###   ########.fr       */
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
		return (ft_printf("minishell: cd: HOME not set\n"), 1);
	if (chdir(path) != 0)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
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
