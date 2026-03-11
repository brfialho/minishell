/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:23:48 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/11 19:16:26 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_shell_signal = 0;

static void		set_shell_status(t_env *env);
static t_bool	process_input_pipeline(t_mini *mini);

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
		mini.input = read_prompt_line(&mini);
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

static t_bool	process_input_pipeline(t_mini *mini)
{
	mini->error_code = NO_ERROR;
	if (!ft_strcmp(mini->input, WHITESPACE))
		return (EXIT_FAILURE);
	mini->error_code = ft_lexer(&mini->lexer, mini->input);
	if (mini->error_code)
		return (lexer_error_handler(mini), EXIT_FAILURE);
	mini->error_code = parser(&mini->root, &mini->lexer);
	if (mini->error_code)
		return (parser_error_handler(mini), EXIT_FAILURE);
	lexer_destroy(&mini->lexer);
	mini->error_code = collect_heredocs(mini);
	if (mini->error_code)
		return (parser_destroy(mini->root), EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
