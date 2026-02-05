/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:05:56 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/04 21:19:17 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


int		builtin_echo(t_cmd *cmd)
{
    int i;
	int newline;
    int j;

	i = 1;
	newline = 1;
	while (cmd->argv[i] && cmd->argv[i][0] == '-' && cmd->argv[i][1] == 'n')
	{
		j = 1;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] != '\0')
			break;
		newline = 0;
		i++;
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

int		builtin_cd(t_cmd *cmd, char **envp)
{
    char    *path;
    char    *cwd;

    cwd = getcwd(NULL, 0);
    if (cmd->argv[0][0] == "cd" && cmd->argv[1] == NULL)
    path = ft_get_envp(&envp, "HOME");
    if (path == NULL)
        perror("Home not set");
    else
        chdir(path);
}

int		builtin_pwd(void)
{
    char *cwd;

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

int		builtin_export(t_cmd *cmd, char ***envp)
{
    
}

int		builtin_unset(t_cmd *cmd, char ***envp)
{
    
}