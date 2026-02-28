/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/27 21:11:13 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_status_shell = 0;


// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	t_lexer lexer_data;

// 	ft_printf("%s\n", argv[1]);
// 	ft_lexer(&lexer_data, argv[1]);
// 	t_ast **root = parser(&lexer_data);
// 	// if (lexer_data.token_lst)
// 	// 	lst_for_each(*(t_list **)(lexer_data.token_lst), print_node);
// 	lexer_destroy(&lexer_data);
// 	parser_destroy(root);
// }

void	print_node_2(void *content)
{
	ft_printf("String: %s Expandable:%d\n", ((t_token *)content)->string, ((t_token *)content)->expandable);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_mini	mini;

// 	ft_bzero(&mini ,sizeof(t_mini));
// 	set_prompt_signals();
// 	while (TRUE)
// 	{
// 		mini.input = read_prompt_line();
// 		if (mini.input == NULL)
// 			continue;
// 		ft_lexer(&mini.lexer, mini.input);
// 		trim_quoted_tokens11(&mini.lexer);
// 		lst_for_each(*mini.lexer.token_lst, print_node_2);
// 	}
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// }

// static void	destroy_cicle(t_mini *mini);

// int	main(int argc, char **argv, char **env)
// {
// 	t_mini	mini;

// 	ft_bzero(&mini ,sizeof(t_mini));
// 	// mini.input = argv[1];
// 	// if (ft_lexer(&mini.lexer, mini.input))
// 	// 	return (EXIT_FAILURE);
// 	// trim_quoted_tokens(&mini.lexer);
// 	// parser(&mini.root, &mini.lexer);
// 	// destroy_cicle(&mini);
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// }

int main(int argc, char **argv)
{
	(void)argc;
	t_mini	mini;

	ft_bzero(&mini ,sizeof(t_mini));
	ft_lexer(&mini.lexer, argv[1]);
	lst_for_each(*mini.lexer.token_lst, print_node_2);
	lexer_destroy(&mini.lexer);
}

// static void	destroy_cicle(t_mini *mini)
// {
// 	lexer_destroy(&mini->lexer);
// 	parser_destroy(mini->root);
// }