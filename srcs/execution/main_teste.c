/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_teste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:35:33 by rafreire          #+#    #+#             */
/*   Updated: 2026/01/20 20:02:42 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int main(void)
{
    t_cmd 	cmd;
	t_redir redir;
    char    *line;

	cmd.heredoc_fd = -1;
	// dados chumbados para teste 
	redir.type = REDIR_HEREDOC;
	redir.target = "EOF";
	redir.next = NULL;
    while (1)
    {
        set_prompt_signals();
        line = read_prompt_line();
        if (!line)
            continue;
        if (set_redir(&redir, &cmd) == -1)
        {
            printf("Heredoc abortado pelo sinal!\n");
        }
        else
        {
            char buffer[1024];
            int n = read(cmd.heredoc_fd, buffer, sizeof(buffer)-1);
            if (n > 0)
            {
                buffer[n] = '\0';
                printf("Conteúdo do heredoc:\n%s", buffer);
            }
            if (cmd.heredoc_fd != -1)
                close(cmd.heredoc_fd);
        }
        printf("Você digitou: %s\n", line);
        free(line);
    }
    return 0;
}
