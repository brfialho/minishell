/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fd_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:22:24 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/11 17:51:36 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	setup_heredoc_to_stdin(char *heredoc_string)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe error");
		return (-1);
	}
	if (heredoc_string != NULL)
	{
		write(pipe_fd[1], heredoc_string, ft_strlen(heredoc_string));
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}
