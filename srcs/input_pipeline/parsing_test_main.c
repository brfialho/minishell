/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/05 21:21:10 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "expansion.h"

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

// void	print_node_2(void *content)
// {
// 	ft_printf("String: %s Expandable:%d\n", ((t_token *)content)->string, ((t_token *)content)->expandable);
// }

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


// int main(void)
// {
// 	int size = 4;
// 	char **argv = ft_calloc(size, sizeof(char *));
// 	// argv[0] = ft_strdup("echo");
// 	// argv[1] = ft_strdup("$EXPAND'$NOEXPAND'\"$EXPAND''\"algumacoisanadahaver$EXPAND");
// 	// argv[2] = ft_strdup("$EXPAND$EXPAND_SPACE$USER");
// 	// argv[3] = NULL;

// 	argv[0] = ft_strdup("$a$b");
// 	argv[1] = ft_strdup("$EXPAND'$NOEXPAND'\"$EXPAND''\"algumacoisanadahaver$EXPAND");
// 	argv[2] = ft_strdup("$EXPAND$EXPAND_SPACE$USER");
// 	argv[3] = NULL;

// 	// argv[0] = ft_strdup("echo");
// 	// argv[1] = NULL;
// 	ft_split_free(expand_argv(argv));
// 	ft_split_free(argv);
// }



// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return 1;
// 	char **split = ft_split_no_quoted(argv[1], ' ');
// 	ft_split_print(split);
// 	ft_split_free(split);
// }

// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (1);

// 	t_mini	mini;

// 	ft_bzero(&mini ,sizeof(t_mini));
	
// 	mini.input = argv[1];
// 	process_input_pipeline(&mini);
	
// 	t_ast *root = *mini.root;
// 	t_msh_ast *content = root->content;
// 	t_redir *heredoc = ((t_list *)*content->redir)->content;

// 	expand_heredoc(heredoc);
// 	// expand_redir(heredoczao);
// 	// destroy_cicle(&mini);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	if (argc != 2)
// 		return 1;

// 	t_mini	mini;
// 	ft_bzero(&mini, sizeof(t_mini));
// 	mini.env = env_from_envp(envp);
// 	mini.input = argv[1];
// 	process_input_pipeline(&mini);

// 	t_ast *root = *mini.root;
// 	t_msh_ast *content = root->content;
// 	char **new_argv = expand_argv(content->argv, &mini.env);
// 	// expand_redir(((t_list *)*content->redir)->content, &mini.env);
// 	// ft_printf("TARGET: %s\n", ((t_redir *)(((t_list *)*content->redir)->content))->target);
// 	expand_heredoc(((t_list *)*content->redir)->content, &mini.env);
// 	ft_printf("TARGET: %s\n", ((t_redir *)(((t_list *)*content->redir)->content))->target);
// 	ft_split_print(new_argv);
// 	ft_split_free(new_argv);
// 	parser_destroy(mini.root);
// 	env_clear(&mini.env);
// 	(void)envp;
// }

int main()
{
	char	buffer[1024] = {0};
	getcwd(buffer, sizeof(buffer));
	ft_printf("%s\n", buffer);
}

// if /home/user/
//	return ~/folder
// else
// 	return start

// "echo \$EXPAND'\$NOEXPAND'\"\$EXPAND\"algumacoisanadahaver\$EXPAND";
// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return 1;
// 	free (expand_string(argv[1]));
// }
// "echo OI\$USER\"\$VAR_VAZIA''\"'\$NAO_EXPANDE'\$VAR_VAZIA''"
// static void	destroy_cicle(t_mini *mini)
// {
// 	lexer_destroy(&mini->lexer);
// 	parser_destroy(mini->root);
// }