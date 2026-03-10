/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:43:39 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/10 19:30:32 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_cleaner_list(t_cmd *list)
{
	t_cmd *next;

	while(list)
	{
		next = list->next;
		destroy_exec_cmd(list);
		free(list);
		list = next;
	}
}

t_cmd	*cmd_add_back(t_cmd *left, t_cmd *right)
{
	t_cmd *tmp;

    if (!left)
        return right;
    tmp = left;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = right;
    return left;
}

void	resolve_pipeline_paths(t_cmd *cmd, t_env **env)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (!is_builtin(current->argv[0]))
		{
			current->path = get_path_dirs(current, env);
		}
		current = current->next;
	}
}

