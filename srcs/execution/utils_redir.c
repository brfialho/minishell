/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:43:34 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/04 09:13:19 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing/parsing.h"
# include "execution/execution.h"
# include "main.h"

int    open_redir_fd(t_redir *redir)
{
    if (redir->type == REDIR_IN)
        return (open(redir->target, O_RDONLY));
    else if (redir->type == REDIR_OUT)
        return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
    else if (redir->type == REDIR_APPEND)
        return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND));
    return (0);
}

int apply_redir_fd(int fd, t_redir *redir)
{
    if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
        return (dup2(fd, STDIN));
    if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
        return (dup2(fd, STDOUT));
    return (-1);
}

int solve_heredoc(t_redir *redir, t_cmd *cmd)
{
    int     fd[2];

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

int read_heredoc_loop(t_redir *redir, int write_fd)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            if (g_status_shell == 130)
                return (-1);
            printf("warning: here-document delimited by end-of-file (wanted `%s')\n", redir->target);
            break;
        }
        if (strcmp(line, redir->target) == 0)
        {
            free(line);
            break;
        }
        write(write_fd, line, ft_strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
    return (0);
}
