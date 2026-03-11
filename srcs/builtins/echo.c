/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 21:24:58 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 21:29:14 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	j;
	int	newline;

	i = 0;
	newline = 1;
	while (cmd->argv[++i] && cmd->argv[i][0] == '-' && cmd->argv[i][1] == 'n')
	{
		j = 1;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] != '\0')
			break ;
		newline = 0;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], STDOUT);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT);
	return (0);
}
