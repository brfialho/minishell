/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:24:30 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 17:34:57 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execution.h"
#include "parser.h"
#include "lexer.h"
#include <unistd.h>

extern int	exec_node(t_ast *node, t_env **env);

void	executor(t_mini *mini)
{
	if (!mini || !mini->root)
		return ;
	mini->exit_status =	exec_node(*mini->root, &mini->env);
}
