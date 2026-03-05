/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:05:48 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/05 15:06:52 by rafreire         ###   ########.fr       */
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
			if (setup_heredoc_to_stdin(cmd->redir->target) == -1)
           		exit(EXIT_FAILURE);
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


