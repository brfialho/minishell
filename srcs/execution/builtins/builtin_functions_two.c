/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:56 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/07 04:27:59 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "main.h"

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

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT);
	free(cwd);
	return (0);
}

int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
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

int builtin_exit(t_cmd *cmd, int is_parent, t_mini *mini)
{
	long long value;
	int status;

	if (is_parent)
		ft_printf("exit\n");
	if (!cmd->argv[1])
		status = g_status_shell;
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
