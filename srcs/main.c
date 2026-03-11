/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:23:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/10 22:36:14 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_shell_signal = 0;

static void	set_shell_status(t_env *env);

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	ft_bzero(&mini, sizeof(t_mini));
	mini.env = env_from_envp(envp);
	set_signals();
	while (TRUE)
	{
		set_shell_status(mini.env);
		mini.input = read_prompt_line();
		if (mini.input == NULL)
		{
			ft_printf("exit\n");
			break;
		}
		if (process_input_pipeline(&mini) == EXIT_FAILURE)
			continue;
		executor(&mini);
		parser_destroy(mini.root);
		mini.root = NULL;
	}
	env_clear(&mini.env);
	return (mini.exit_status);
}

static void	set_shell_status(t_env *env)
{
	char	*value;

	if (!g_shell_signal)
		return ;
	value = ft_itoa(g_shell_signal + 128);
	ft_set_env(&env, "?", value);
	free(value);
}
