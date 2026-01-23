/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/23 18:53:36 by brfialho         ###   ########.fr       */
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
	t_list **token_lst;

	token_lst = ft_calloc(1, sizeof(t_list *));
	if (!token_lst)
		return (1);
	ft_printf("%s\n", argv[1]);
	lexer(token_lst, argv[1]);
	if (token_lst)
		lst_for_each(*token_lst, print_node);
	lst_del_all(token_lst, del);
	free(token_lst);
}
