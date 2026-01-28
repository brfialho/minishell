/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/28 18:51:14 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_node(void *content)
{
	ft_printf("Token: %d String: %s\n", ((t_token *)content)->code, ((t_token *)content)->string);
}

void	del(void *content)
{
	t_token *token = content;
	free(token->string);
	free(token);
}



int main(int argc, char **argv)
{
	(void) argc;
	t_lexer lexer_data;

	ft_printf("%s\n", argv[1]);
	lexer(&lexer_data, argv[1]);
	if (lexer_data.token_lst)
		lst_for_each(*(t_list **)(lexer_data.token_lst), print_node);
	lst_del_all(lexer_data.token_lst, del);
	free(lexer_data.token_lst);
}
