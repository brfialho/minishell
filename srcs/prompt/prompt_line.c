/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:06:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/05 12:58:14 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*read_prompt_line(void)
{
	char	*line;
	
	line = readline(PROMPT);
	if (!line)
    	return (NULL);
	if (!*line || ft_str_allinset(line, WHITESPACE))
	{
    	free(line);
    	return (NULL);
	}
	add_history(line);
	return (line);
}
