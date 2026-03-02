/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:01 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/02 16:10:23 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	**expand_argv(char **old_argv)
{
	char	**argv;
	char	*full_argv;
	int		i;

	i = -1;
	while (old_argv[++i])
		old_argv[i] = expand_string(old_argv[i]);
	i = 0;
	full_argv = ft_strdup(old_argv[i]);
	while (old_argv[++i])
	{
		full_argv = ft_strjoin_free(full_argv, " ", TRUE, FALSE);
		full_argv = ft_strjoin_free(full_argv, old_argv[i], TRUE, FALSE); 
	}
	argv = ft_split(full_argv, ' ');
	free(full_argv);
	ft_split_print(argv);
	return (argv);
}
