/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:24:30 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/01 21:50:21 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execution.h"
#include "parser.h"
#include "lexer.h"
#include <unistd.h>

extern int	exec_node(t_ast *node, t_env **env);
extern char	**environ; // temporario para acessar variáveis de ambiente, pode ser removido depois que a estrutura de ambiente estiver implementada

static t_env	*init_execution_env(void)
{
	t_env	*exec_env;

	exec_env = env_from_envp(environ);
	return (exec_env);
}

static int	execute_ast_flow(t_ast **root)
{
	t_env	*exec_env;
	int		status;

	if (!root)
		return (0);
	exec_env = init_execution_env();
	status = exec_node(*root, &exec_env);
	g_status_shell = status;
	return (status);
}

void	executor(t_mini *mini)
{
	if (!mini || !mini->root)
		return ;
	execute_ast_flow(mini->root);
}

