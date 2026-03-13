/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 21:26:26 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/13 19:20:36 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(t_env *env, t_cmd *cmd)
{
	if (cmd->argv[1])
	{
		ft_printf("Minishell: env: '%s': No arguments allowed\n",
			cmd->argv[1]);
		return (127);
	}
	while (env)
	{
		if (env->value && ft_strcmp(env->key, "?"))
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
