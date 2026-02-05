/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:43:15 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/04 14:04:03 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		ft_exec_cmd(t_cmd *cmd, char ***envp)
{
    pid_t   pid;
    int     status;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (0);
    if (cmd->argv[0][0] == '\0')
    {
        ft_putendl_fd("minishell: : command not found", 2);
        return (127);
    }
    if (is_builtin(cmd->argv[0]))
        return(execute_builtin(cmd, &envp));
    pid = fork();
    if (pid == -1)
        return (printf("fork"));
    if (pid == 0)
    {
        // aplicar redirecionamentos
        // execve
    }    
    // 5. PROCESSO PAI
    waitpid(pid, &status, 0);
    return (calcular_exit_status(status));
    return (status);
}




