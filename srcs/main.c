/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:23:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 17:32:57 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_status_shell = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	ft_bzero(&mini, sizeof(t_mini));
	mini.env = env_from_envp(envp);
    mini.should_exit = 0;
	set_prompt_signals();
	while (!mini.should_exit)
	{
		mini.input = read_prompt_line();
		if (mini.input == NULL)
			continue;
		if (process_input_pipeline(&mini) == EXIT_FAILURE)
			continue;
		executor(&mini);
		lexer_destroy(&mini.lexer);
		parser_destroy(mini.root);
	}
	env_clear(&mini.env);
	return (mini.exit_status);
}

