/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:24:30 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/12 22:28:49 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execution.h"
#include "parser.h"
#include "lexer.h"
#include <unistd.h>

extern int	exec_node(t_ast *node, t_env **env, t_mini *mini);

void	executor(t_mini *mini)
{
	char	*value;

	if (!mini || !mini->root)
		return ;
	mini->exit_status = exec_node(*mini->root, &mini->env, mini);
	value = ft_itoa(mini->exit_status);
	ft_set_env(&mini->env, "?", value);
	free(value);
}
