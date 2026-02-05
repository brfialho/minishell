/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:06:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/04 08:57:16 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing/parsing.h"
# include "execution/execution.h"
# include "main.h"

char    *read_prompt_line(void)
{
    char    *line;

    line = readline("minishell$ ");
    if (!line)
    {
        printf("exit\n");
        return (NULL);
    }
    if (g_status_shell == 130)
    {
        g_status_shell = 0;
        free(line);
        return (NULL);
    }
    if (*line)
        add_history(line);
    return line;
}
