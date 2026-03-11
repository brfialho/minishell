/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:24:30 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 23:09:04 by brfialho         ###   ########.fr       */
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
	if (!mini || !mini->root)
		return ;
	mini->exit_status = exec_node(*mini->root, &mini->env, mini);
}
