/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:22:05 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/21 18:39:15 by brfialho         ###   ########.fr       */
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
	t_list			*lst;
	t_token_code	prev_code;

	lst = *lexer->token_lst;
	prev_code = 0;
	while (lst)
	{
		if (ft_str_charcount("\"'", ((t_token *)lst->content)->string[0])
			&& prev_code != HEREDOC)
			trim_quotes(lst->content);
		prev_code = ((t_token *)lst->content)->code;
		lst = lst->next;
	}
}

void	parsing(t_mini *mini)
{
	ft_lexer(&mini->lexer, mini->input);
	trim_quoted_tokens(&mini->lexer);
	mini->root = parser(&mini->lexer);
}
