/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:22:24 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/21 19:03:07 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	solve_heredoc(t_n_redir *redir, t_cmd *cmd)
{
	int	fd[2];

	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	cmd->heredoc_fd = -1;
	if (pipe(fd) == -1)
		return (-1);
	if (read_heredoc_loop(redir, fd[1]) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	close(fd[1]);
	cmd->heredoc_fd = fd[0];
	return (0);
}

int	read_heredoc_loop(t_n_redir *redir, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_status_shell == 130)
				return (-1);
			printf
			("warning: here-document delimited,by end-of-file (wanted `%s')\n",
				redir->target);
			break ;
		}
		if (strcmp(line, redir->target) == 0)
		{		
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int prepare_heredocs(t_n_redir *redir, t_cmd *cmd)
{
    while (redir)
    {
        if (redir->type == REDIR_HEREDOC)
        {
            if (solve_heredoc(redir, cmd) == -1)
                return (-1);
        }
        redir = redir->next;
    }
    return (0);
}
