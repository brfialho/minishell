/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:43:34 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/21 19:31:47 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	open_redir_fd(t_n_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open(redir->target, O_RDONLY));
	else if (redir->type == REDIR_OUT)
		return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == REDIR_APPEND)
		return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND));
	return (0);
}

int	apply_redir_fd(int fd, t_n_redir *redir)
{
	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
		return (dup2(fd, STDIN_FILENO));
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		return (dup2(fd, STDOUT_FILENO));
	return (-1);
}
	

t_n_redir *new_exec_redir(t_redir *ast_redir)
{
	t_n_redir *new;

	new = safe_calloc(1, sizeof(t_n_redir));
	if (!new)
		return (NULL);
	new->type = ast_redir->type;
	new->target = ft_strdup(ast_redir->target);
	if (!new->target)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_n_redir *convert_redir_list(t_list *ast_list)
{
	t_n_redir	*head;
	t_n_redir	*last;
	t_n_redir	*new_node;
	t_redir		*ast_redir;

	head = NULL;
	last = NULL;
	while (ast_list)
	{
		ast_redir = (t_redir *)ast_list->content;
		new_node = new_exec_redir(ast_redir);
		if (!new_node)
		{
			free_exec_redir_list(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			last->next = new_node;
		last = new_node;
		ast_list = ast_list->next;
	}
	return (head);
}

void free_exec_redir_list(t_n_redir *redir)
{
	t_n_redir *tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}
