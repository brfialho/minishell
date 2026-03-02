/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:23:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/01 21:43:08 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_status_shell = 0;

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	(void)env;
	ft_bzero(&mini, sizeof(t_mini));
	set_prompt_signals();
	while (TRUE)
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
	return (EXIT_SUCCESS);
}

