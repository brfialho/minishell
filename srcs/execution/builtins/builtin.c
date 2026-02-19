/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:21 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 17:47:11 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	execute_builtin(t_cmd *cmd, t_env **env)
{
	char	*builtin;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	builtin = cmd->argv[0];
	if (!strcmp(builtin, "echo"))
		return (builtin_echo(cmd));
	if (!strcmp(builtin, "cd"))
		return (builtin_cd(cmd, env));
	if (!strcmp(builtin, "pwd"))
		return (builtin_pwd());
	if (!strcmp(builtin, "export"))
		return (builtin_export(cmd, env));
	if (!strcmp(builtin, "unset"))
		return (builtin_unset(cmd, env));
	if (!strcmp(builtin, "env"))
		return (builtin_env(*env));
	if (!strcmp(builtin, "exit"))
		return (builtin_exit());
	return (1);
}
