/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:05:48 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/24 20:30:21 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"
# include "execution.h"
# include "set_signal.h"

int apply_redirections(t_n_redir *redir, t_cmd *cmd)
{
	int fd;

	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			if (cmd->heredoc_fd != -1)
				dup2(cmd->heredoc_fd, STDIN_FILENO);
		}
		else
		{
			fd = open_redir_fd(redir);
			if (fd == -1)
				return (-1);
			if (apply_redir_fd(fd, redir) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}


