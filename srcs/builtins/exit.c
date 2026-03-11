/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:56 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/10 23:03:13 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "main.h"

static int	is_valid_number(const char *str, long long *value);

int	builtin_exit(t_cmd *cmd, int is_parent, t_mini *mini)
{
	long long	value;
	int			status;

	if (is_parent)
		ft_printf("exit\n");
	if (!cmd->argv[1])
		status = g_shell_signal;
	else if (!is_valid_number(cmd->argv[1], &value))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		status = 2;
	}
	else if (cmd->argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	else
		status = (unsigned char)value;
	rl_clear_history();
	cleanup_exit(cmd, mini);
	exit(status);
}

static int	is_valid_number(const char *str, long long *value)
{
	char	*endptr;

	errno = 0;
	*value = strtoll(str, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		return (0);
	return (1);
}
