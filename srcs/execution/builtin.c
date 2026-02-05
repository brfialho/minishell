/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:21 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/04 14:36:10 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int execute_builtin(t_cmd *cmd, char ***envp)
{
    char    *builtin_name;

    if (!cmd || !cmd->argv[0])
        return(1);
    builtin_name = cmd->argv[0];
    if (strcmp(builtin_name, "echo") == 0)
        return(builtin_echo(cmd));
    if (strcmp(builtin_name, "cd") == 0)
        return(builtin_cd(cmd, *envp));
    if (strcmp(builtin_name, "pwd") == 0)
        return(builtin_pwd());
    if (strcmp(builtin_name, "export") == 0)
        return(builtin_export(cmd, *envp));
    if (strcmp(builtin_name, "unset") == 0)
        return(builtin_unset(cmd, *envp));
    if (strcmp(builtin_name, "env") == 0)
        return(builtin_env(*envp));
    if (strcmp(builtin_name, "exit") == 0)
        return(builtin_exit(cmd));
}
