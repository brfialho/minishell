/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:21 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/06 10:59:55 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int execute_builtin(t_cmd *cmd, t_env **env)
{
	char *builtin;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	builtin = cmd->argv[0];
	if (!ft_strcmp(builtin, "echo"))
		return (builtin_echo(cmd));
	if (!ft_strcmp(builtin, "cd"))
		return (builtin_cd(cmd, env));
	if (!ft_strcmp(builtin, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(builtin, "export"))
		return (builtin_export(cmd, env));
	if (!ft_strcmp(builtin, "unset"))
		return (builtin_unset(cmd, env));
	if (!ft_strcmp(builtin, "env"))
		return (builtin_env(*env));
	if (!ft_strcmp(builtin, "exit"))
		return (builtin_exit(cmd));
	return (1);
}
