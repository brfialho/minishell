/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:43:39 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 13:12:46 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_cleaner_list(t_cmd *list)
{
	char *next;

	while(list)
	{
		next = list->next;
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
