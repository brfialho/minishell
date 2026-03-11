/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 21:22:45 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 21:23:03 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_export(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*eq;

	if (!cmd->argv[1])
		return (env_print_sorted(*env), 0);
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
