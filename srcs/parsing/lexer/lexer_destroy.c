/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:44:30 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 03:23:55 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	del_token(void	*content);
static char	*get_arrow_string(const char *input, const char *end);

void	lexer_destroy(t_lexer *lexer)
{
	if (*lexer->token_lst)
		lst_del_all(lexer->token_lst, del_token);
	free(lexer->token_lst);
	lexer->token_lst = NULL;
}

void	lexer_quotes_error(t_lexer *lexer, const char *input)
{
	char	quote;
	char	*arrow;

	quote = '\'';
	if (lexer->state == IN_D_QUOTES)
		quote = '"';
	arrow =get_arrow_string(input, lexer->unclosed_quotes);
	ft_printf(BOLD "-------------%s" "^\n" RESET, arrow);
	ft_printf(QUOTE_ERROR BOLD " %c\n" RESET, quote);
	free(arrow);
	lexer_destroy(lexer);
}

static char	*get_arrow_string(const char *input, const char *end)
{
	char	*arrow;
	char	*s;
	int 	i;

	arrow = ft_safe_calloc(ft_strlen(input) + 1, sizeof(char));
	s = (char *)input;
	i = 0;
	while (s++ != end)
		arrow[i++] = '-';
	arrow[i] = '\0';
	return (arrow);
}

static void	del_token(void	*content)
{
	t_token	*token;

	token = content;
	if (token->code == WORD)
		free(token->string);
	free(token);
}
