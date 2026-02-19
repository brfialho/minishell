/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:06:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 17:40:27 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*read_prompt_line(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!*line)
		return (NULL);
	if (!ft_strncmp(line, "exit", ft_strlen("exit")))
		exit(1);
	add_history(line);
	return (line);
}
	// if (g_status_shell == 130)
	// {
	// 	g_status_shell = 0;
	// 	free(line);
	// 	return (NULL);
	// }