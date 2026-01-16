/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:30:38 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/16 17:59:51 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef enum e_redir_type
{
	REDIR_IN = 1,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
} t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target; //file name ou delimiter
	struct s_redir	*next;
} t_redir;

int		set_redir(t_redir *redir);
int		open_redir_fd(t_redir *redir);
int		apply_redir_fd(int fd, t_redir *redir);

#endif