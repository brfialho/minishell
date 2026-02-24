/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:06:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/24 00:56:37 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*read_prompt_line(void)
{
	char	*line;

	line = readline(PROMPT);
	if (!*line)
		return (NULL);
	if (!ft_strncmp(line, "exit", ft_strlen("exit")))
		builtin_exit();
	add_history(line);
	return (line);
}
