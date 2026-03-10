/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:24:30 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 08:53:48 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execution.h"
#include "parser.h"
#include "lexer.h"
#include <unistd.h>

extern int	exec_node(t_ast *node, t_env **env, t_mini *mini);
extern int	g_shell_state;

void	executor(t_mini *mini)
{
	if (!mini || !mini->root)
		return ;
	mini->exit_status =	exec_node(*mini->root, &mini->env, mini);
	g_shell_state = mini->exit_status;
}
