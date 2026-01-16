/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:43:15 by rafreire          #+#    #+#             */
/*   Updated: 2026/01/16 18:08:36 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	set_redir(t_redir *redir)
{
    int fd;

    while(redir)
    {
        fd = open_redir_fd(redir);
        if(fd == -1)
            return (-1);
        if(apply_redir_fd(fd, redir) == -1)
        {
            close(fd);
            return (-1);
        }
        close(fd);
        redir = redir->next;
    }
    return (0);
}



