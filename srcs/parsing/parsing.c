/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:22:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/21 00:20:42 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	trim_quotes(t_token *token)
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

void	trim_quoted_tokens(t_lexer *lexer)
{
	t_list	*lst;

	lst = *lexer->token_lst;
	while (lst)
	{
		if (ft_str_charcount("\"'", ((t_token *)lst->content)->string[0]))
			trim_quotes(lst->content);
		lst = lst->next;
	}
}

void	parsing(t_mini *mini)
{
	ft_lexer(&mini->lexer, mini->input);
	trim_quoted_tokens(&mini->lexer);
	mini->root = parser(&mini->lexer);
}
