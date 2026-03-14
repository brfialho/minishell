/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 21:22:45 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/14 18:26:59 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_bool	validate_key_name(char	*s, int *status);

int	builtin_export(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*eq;
	int		status;

	if (!cmd->argv[1])
		return (env_print_sorted(*env), 0);
	i = 0;
	status = 0;
	while (cmd->argv[++i])
	{
		eq = ft_strchr(cmd->argv[i], '=');
		if (eq)
			*eq = '\0';
		if (validate_key_name(cmd->argv[i], &status))
			continue ;
		if (!eq)
		{
			ft_set_env(env, cmd->argv[i], NULL);
			continue ;
		}	
		ft_set_env(env, cmd->argv[i], eq + 1);
		*eq = '=';
	}
	return (status);
}

static t_bool	validate_key_name(char	*s, int *status)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_str_charcount(ARGV_EXPAND_DELIMITER, s[i]))
		{
			*status = 1;
			ft_printf(EXPORT_NAME_ERROR, s);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
