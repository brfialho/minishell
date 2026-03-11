/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 21:46:26 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/11 19:14:28 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*get_arrow_string(const char *input, const char *end,  int prompt_len);

void	lexer_error_handler(t_mini *mini)
{
	char	quote;
	char	*arrow;

	quote = '\'';
	if (mini->lexer.state == IN_D_QUOTES)
		quote = '"';
	arrow = get_arrow_string(mini->input, mini->lexer.unclosed_quotes, mini->prompt_len);
	ft_printf(BOLD "%s^\n" RESET, arrow);
	ft_printf(QUOTE_ERROR BOLD " %c\n" RESET, quote);
	free(arrow);
	lexer_destroy(&mini->lexer);
	mini->error_code = UNCLOSED_QUOTES;
}

static char	*get_arrow_string(const char *input, const char *end, int prompt_len)
{
	char	*arrow;
	char	*s;
	int		i;

	arrow = ft_safe_calloc(ft_strlen(input) + prompt_len + 1, sizeof(char));
	i = 0;
	while (i < prompt_len)
		arrow[i++] = '-';
	s = (char *)input;
	while (s++ != end)
		arrow[i++] = '-';
	return (arrow);
}
