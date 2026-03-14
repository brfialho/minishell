/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:09:12 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/13 21:16:26 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exec_error_handler(t_mini *mini, int status)
{
	env_clear(&mini->env);
	ft_cleaner_list(mini->current_cmd_head);
	parser_destroy(mini->root);
	exit(status);
}
