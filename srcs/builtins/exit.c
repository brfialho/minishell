/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:56 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/11 18:23:15 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "main.h"

static int			is_valid_number(const char *str, long long *value);
static long long	exit_atoll(char *s, t_bool *error);

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
	t_bool	error;

	error = 0;
	*value = exit_atoll((char *)str, &error);
	printf("ld: %lld\nEROR:%d\n", *value, error);
	return ((error == 0));
}

static long long	exit_atoll(char *s, t_bool *error)
{
	long long	sum;
	int			sign;

	sign = 1;
	sum = 0;
	if (*s == '+' || *s == '-')
	{		
		if (*s == '-' && s++)
			sign = -1;
		else
			s++;
	}
	while (*s)
	{
		if (!ft_isdigit(*s))
			*error = TRUE;
		if (sum * 10 + *s - '0' < sum)
			*error = TRUE;
		sum = sum * 10 + *s++ - '0';
	}
	return (sum * sign);
}
