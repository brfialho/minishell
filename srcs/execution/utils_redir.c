/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:43:34 by rafreire          #+#    #+#             */
/*   Updated: 2026/01/16 18:08:40 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int    open_redir_fd(t_redir *redir)
{
    if(redir->type == REDIR_IN)
        return (open(redir->target, O_RDONLY));
    else if(redir->type == REDIR_OUT)
        return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
    else if(redir->type == REDIR_APPEND)
        return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND));
    else if(redir->type == REDIR_HEREDOC)
    {
        //implementar
    }
    return (0);
}

int apply_redir_fd(int fd, t_redir *redir)
{
    if(redir->type == REDIR_IN)
        return(dup2(fd, STDIN));
    else if(redir->type == REDIR_OUT)
        return(dup2(fd, STDOUT));
    else if(redir->type == REDIR_APPEND)
        return(dup2(fd, STDOUT));
    else if(redir->type == REDIR_HEREDOC)
        return(dup2(fd, STDIN));
    return (0);
}
