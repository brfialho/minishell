/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/09 19:30:19 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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



int main(int argc, char **argv)
{
	(void) argc;
	t_lexer lexer_data;

	ft_printf("%s\n", argv[1]);
	ft_lexer(&lexer_data, argv[1]);
	// if (lexer_data.token_lst)
	// 	lst_for_each(*(t_list **)(lexer_data.token_lst), print_node);
	lexer_destroy(&lexer_data);
}
