/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/21 18:38:48 by brfialho         ###   ########.fr       */
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

void parser_destroy(t_ast **root)
{
	ast_del_all(root, del_ast_node);
	free(root);
}

void	print_node(void *content)
{
	ft_printf("Code: %d String: %s\n", ((t_token *)content)->code, ((t_token *)content)->string);
}

void	del(void *content)
{
	t_token *token = content;

	if (token->code == WORD)
		free(token->string);
	free(token);
}

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
	ft_printf("Code: %d String: %s Expandable:%d\n", ((t_token *)content)->code, ((t_token *)content)->string, ((t_token *)content)->expandable);
}

void	trim_quotes11(t_token *token)
{
	char	*new;
	int		len;

	len = ft_strlen(token->string);
	if (len == 2)
	{
		free(token->string);
		token->string = safe_calloc(1, sizeof(char));
		return ;
	}
	new = safe_calloc(len - 1, sizeof(char));
	ft_memcpy(new, token->string + 1, len - 2);
	free(token->string);
	token->string = new;
}

void	trim_quoted_tokens11(t_lexer *lexer)
{
	t_list			*lst;
	t_token_code	prev_code;

	lst = *lexer->token_lst;
	prev_code = 0;
	while (lst)
	{
		if (ft_str_charcount("\"'", ((t_token *)lst->content)->string[0])
			&& prev_code != HEREDOC)
			trim_quotes11(lst->content);
		prev_code = ((t_token *)lst->content)->code;
		ft_printf("PREV %d\n", prev_code);
		lst = lst->next;
	}
}

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
		ft_lexer(&mini.lexer, mini.input);
		trim_quoted_tokens11(&mini.lexer);
		lst_for_each(*mini.lexer.token_lst, print_node_2);
	}
	(void)argc;
	(void)argv;
	(void)env;
}