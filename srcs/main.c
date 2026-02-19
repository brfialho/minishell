/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:23:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/19 17:10:19 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_status_shell = 0;

void	del_ast_node(void *content)
{
	t_msh_ast	*ast;

	ast = content;
	if (ast->type == NODE_EXEC)
	{
		free(ast->argv);
		lst_del_all(ast->redir, free);
		free(ast->redir);
	}
	free (content);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	ft_bzero(&mini ,sizeof(t_mini));
	while (1)
	{
		mini.input = readline("$Minishell ");
		if (!ft_strncmp(mini.input, "exit", ft_strlen("exit")))
			exit(1);
		if (!*mini.input)
		{
			free(mini.input);
			continue;
		}
		ft_lexer(&mini.lexer, mini.input);
		mini.root = parser(&mini.lexer);
		// exec
		lexer_destroy(&mini.lexer);
		ast_del_all(mini.root, del_ast_node);
		free(mini.root);
		free(mini.input);
	}
	(void)argc;
	(void)argv;
	(void)env;
}

