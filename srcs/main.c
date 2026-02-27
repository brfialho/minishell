/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:23:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/27 20:17:53 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_status_shell = 0;

static void	destroy_cicle(t_mini *mini);

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	ft_bzero(&mini ,sizeof(t_mini));
	set_prompt_signals();
	while (TRUE)
	{
		mini.input = read_prompt_line();
		if (mini.input == NULL)
			continue;
		if (process_input_pipeline(&mini))
			continue;
		executor(&mini);
		destroy_cicle(&mini);
	}
	(void)argc;
	(void)argv;
	(void)env;
}

static void	destroy_cicle(t_mini *mini)
{
	lexer_destroy(&mini->lexer);
	parser_destroy(mini->root);
}
