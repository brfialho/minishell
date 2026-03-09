/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:23:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/09 19:30:48 by rafreire         ###   ########.fr       */
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
	set_signals();
	while (!mini.should_exit)
	{
		mini.input = read_prompt_line();
		if (mini.input == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		if (process_input_pipeline(&mini) == EXIT_FAILURE)
			continue ;
		executor(&mini);
		parser_destroy(mini.root);
		mini.root = NULL;
	}
	env_clear(&mini.env);
	return (mini.exit_status);
}
