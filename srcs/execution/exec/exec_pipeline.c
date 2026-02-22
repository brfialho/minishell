/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:07:51 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/21 19:37:42 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"

int	exec_pipeline_list(t_cmd *cmd, t_env **env)
{
	if (!cmd)
		return (0);
	if (cmd->argv[0][0] == '\0')
	{
		ft_putendl_fd("minishell: : command not found", 2);
		return (127);
	}
	if (prepare_heredocs(cmd->redir, cmd) == -1)
		return (130);
}

