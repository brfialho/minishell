/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:57:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/23 17:38:20 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*skip_spaces(const char *input)
{
	while (*input == ' ')
		input++;
	return ((char *)input);
}

t_token	*get_token(t_lexer *lexer)
{
	int i;
	
	lexer->token = ft_calloc(1, sizeof(t_lexer));
	if (!lexer->token)
		return (NULL);
	i = 0;
	while (lexer->left[i] && !ft_strchr(META, lexer->left[i]))
		i++;
	if (!i)
		i++;
	lexer->token->string = ft_calloc(i + 1, sizeof(char));
	if (!lexer->token->string)
		return (free(lexer->token), NULL);
	ft_memcpy(lexer->token->string, lexer->left, i);
	lexer->left = lexer->left + i;
	return (NULL);	
}

void	lexer(t_list **head, const char *input)
{
	t_lexer	lexer;

	ft_bzero(&lexer, sizeof(t_lexer));
	lexer.left = skip_spaces(input);
	while (*lexer.left)
	{
		get_token(&lexer);
		if (lexer.token)
			lst_add_end(head, lst_new_node(lexer.token));
	}
}