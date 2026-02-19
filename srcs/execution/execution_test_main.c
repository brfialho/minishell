/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:39:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 18:51:11 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_status_shell = 0;

void check_node_type(t_msh_ast *content)
{
	if (content->type == NODE_EXEC)
		ft_printf("EXEC\n");
}

int main(int argc, char **argv, char **env)
{
	t_mini mini;

	ft_printf("Main de teste para exec!\n");
	ft_lexer(&mini.lexer, "|");
	mini.root = parser(&mini.lexer);

	t_msh_ast *content = (*mini.root)->content;
	check_node_type(content);
	(void)argc;
	(void)argv;
	(void)env;
}
