/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:56 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/14 00:31:35 by brfialho         ###   ########.fr       */
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
		status = ft_atoi(get_env_value(mini->env, "?"));
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
			return (*error = TRUE, EXIT_FAILURE);
		if (sum >= LONG_MAX / 10
			&& ((sign > 0 && *s > '7')
				|| (sign < 0 && *s > '8')))
			return (*error = TRUE, EXIT_FAILURE);
		sum = sum * 10 + *s++ - '0';
	}
	return (sum * sign);
}
