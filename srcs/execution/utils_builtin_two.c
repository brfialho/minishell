/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:30:44 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/04 21:11:07 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		builtin_env(char **envp)
{
    
}

int		builtin_exit(t_cmd *cmd)
{
    
}

char    *ft_get_envp(char **envp, char *key)
{
	int		i;

    i = 0;
	while(*envp && ft_strncmp(*envp, key, 5) != 0)
    {
        
		envp++;
    }
	return(NULL);
}