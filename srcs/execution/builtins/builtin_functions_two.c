/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:56 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 17:46:25 by brfialho         ###   ########.fr       */
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
	while (cmd->argv[i++] && cmd->argv[i][0] == '-' && cmd->argv[i][1] == 'n')
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
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	builtin_exit(void)
{
	ft_printf("exit\n");
	exit(0);
}
