/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:39:21 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/21 19:53:12 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int g_status_shell = 0;

char	test_helper(char expec_precedence, t_token_code expc_code, char *expec_s, char expec_expand, t_token token)
{
	if (token.code != expc_code
		|| ft_strncmp(expec_s, token.string, ft_strlen(token.string))
		|| token.precedence != expec_precedence
		|| token.expandable != expec_expand)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	test_lexer_simple_input(t_lexer *lexer)
{
	t_token	expected_token[100];
	t_token	*token;
	t_list *lst = *lexer->token_lst;


	if (!lst || lst_size(lst) != 4)
		return (EXIT_FAILURE);

	expected_token[0] = (t_token){WORD, "ls", 0, TRUE};
	expected_token[1] = (t_token){PIPE, "|", 1, FALSE};
	expected_token[2] = (t_token){WORD, "wc", 0, TRUE};
	expected_token[3] = (t_token){WORD, "-l", 0, TRUE};

	int i = -1;
	while (++i < lst_size(lst))
	{
		token = (t_token *)lst->content;
			if (test_helper(expected_token[i].precedence, expected_token[i].code, expected_token[i].string, expected_token[i].expandable,*token))
				return(EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

char	test_lexer_simple_input_no_spaces(t_lexer *lexer)
{
	t_token	expected_token[100];
	t_token	*token;
	t_list *lst = *lexer->token_lst;


	if (!lst || lst_size(lst) != 3)
		return (EXIT_FAILURE);

	expected_token[0] = (t_token){WORD, "ls", 0, TRUE};
	expected_token[1] = (t_token){PIPE, "|", 1, FALSE};
	expected_token[2] = (t_token){WORD, "grep", 0, TRUE};

	int i = -1;
	while (++i < lst_size(lst))
	{
		token = (t_token *)lst->content;
			if (test_helper(expected_token[i].precedence, expected_token[i].code, expected_token[i].string, expected_token[i].expandable,*token))
				return(EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

char	test_lexer_complex_input(t_lexer *lexer)
{
	t_token	expected_token[100];
	t_token	*token;
	t_list *lst = *lexer->token_lst;


	if (!lst || lst_size(lst) != 14)
		return (EXIT_FAILURE);

	expected_token[0] = (t_token){WORD, "echo", 0, TRUE};
	expected_token[1] = (t_token){WORD, "\"Hello world $teste \"", 0, TRUE};
	expected_token[2] = (t_token){PIPE, "|", 1, FALSE};
	expected_token[3] = (t_token){WORD, "wc", 0, TRUE};
	expected_token[4] = (t_token){WORD, "-l", 0, TRUE};
	expected_token[5] = (t_token){OUTFILE, ">", 0, FALSE};
	expected_token[6] = (t_token){WORD, "outfile.txt", 0, TRUE};
	expected_token[7] = (t_token){LOGICAL_AND, "&&", 2, FALSE};
	expected_token[8] = (t_token){WORD, "cat", 0, TRUE};
	expected_token[9] = (t_token){WORD, "outfile.txt", 0, TRUE};
	expected_token[10] = (t_token){LOGICAL_AND, "&&", 2, FALSE};
	expected_token[11] = (t_token){WORD, "rm", 0, TRUE};
	expected_token[12] = (t_token){WORD, "-rf", 0, TRUE};
	expected_token[13] = (t_token){WORD, "outfile.txt", 0, TRUE};

	int i = -1;
	while (++i < lst_size(lst))
	{
		token = (t_token *)lst->content;
			if (test_helper(expected_token[i].precedence, expected_token[i].code, expected_token[i].string, expected_token[i].expandable,*token))
				return(EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

char	test_lexer_complex_with_exports(t_lexer *lexer)
{
	t_token	expected_token[100];
	t_token	*token;
	t_list *lst = *lexer->token_lst;

	// ft_printf("SIZE: %d\n", lst_size(lst));
	if (!lst || lst_size(lst) != 11)
		return (EXIT_FAILURE);

	expected_token[0] = (t_token){WORD, "export", 0, TRUE};
	expected_token[1] = (t_token){WORD, "a", 0, TRUE};
	expected_token[2] = (t_token){ASSIGNMENT, "=", 0, FALSE};
	expected_token[3] = (t_token){WORD, "ech", 0, TRUE};
	expected_token[4] = (t_token){LOGICAL_AND, "&&", 2, FALSE};
	expected_token[5] = (t_token){WORD, "export", 0, TRUE};
	expected_token[6] = (t_token){WORD, "b", 0, TRUE};
	expected_token[7] = (t_token){ASSIGNMENT, "=", 0, FALSE};
	expected_token[8] = (t_token){WORD, "\"o EEEBA\"", 0, TRUE};
	expected_token[9] = (t_token){LOGICAL_AND, "&&", 2, FALSE};
	expected_token[10] = (t_token){WORD, "$a$b", 0, TRUE};

	int i = -1;
	while (++i < lst_size(lst))
	{
		token = (t_token *)lst->content;
		// ft_printf("EXPEC_CODE:%d CODE:%d\nEXPEC_STR:%s STR:%s\n\n", expected_token[i].code, token->code, expected_token[i].string, token->string);
			if (test_helper(expected_token[i].precedence, expected_token[i].code, expected_token[i].string, expected_token[i].expandable,*token))
				return(EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

char	test_lexer_complex_quoted_with_expandable_and_not_expandable(t_lexer *lexer)
{
	t_token	expected_token[100];
	t_token	*token;
	t_list *lst = *lexer->token_lst;

	// ft_printf("SIZE: %d\n", lst_size(lst));
	if (!lst || lst_size(lst) != 13)
		return (EXIT_FAILURE);

	//"echo ola\"$USER\"seu\" \"pid$$'$USER''hello'''ola\"oi\"\"\"t";
	expected_token[0] = (t_token){WORD, "echo", 0, TRUE};
	expected_token[1] = (t_token){WORD, "ola", 0, TRUE};
	expected_token[2] = (t_token){WORD, "\"$USER\"", 0, TRUE};
	expected_token[3] = (t_token){WORD, "seu", 0, TRUE};
	expected_token[4] = (t_token){WORD, "\" \"", 0, TRUE};
	expected_token[5] = (t_token){WORD, "pid$$", 0, TRUE};
	expected_token[6] = (t_token){WORD, "'$USER'", 0, FALSE};
	expected_token[7] = (t_token){WORD, "'hello'", 0, FALSE};
	expected_token[8] = (t_token){WORD, "''", 0, FALSE};
	expected_token[9] = (t_token){WORD, "ola", 0, TRUE};
	expected_token[10] = (t_token){WORD, "\"oi\"", 0, TRUE};
	expected_token[11] = (t_token){WORD, "\"\"", 0, TRUE};
	expected_token[12] = (t_token){WORD, "t", 0, TRUE};

	int i = -1;
	while (++i < lst_size(lst))
	{
		token = (t_token *)lst->content;
		// ft_printf("EXPEC_CODE:%d CODE:%d\nEXPEC_STR:%s STR:%s\n\n", expected_token[i].code, token->code, expected_token[i].string, token->string);
			if (test_helper(expected_token[i].precedence, expected_token[i].code, expected_token[i].string, expected_token[i].expandable,*token))
				return(EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

char	test_lexer_complex_quote_sequence(t_lexer *lexer)
{
	t_token	expected_token[100];
	t_token	*token;
	t_list *lst = *lexer->token_lst;

	// ft_printf("SIZE: %d\n", lst_size(lst));
	if (!lst || lst_size(lst) != 4)
		return (EXIT_FAILURE);

	// "echo \"'\"''\"'\"";
	expected_token[0] = (t_token){WORD, "echo", 0, TRUE};
	expected_token[1] = (t_token){WORD, "\"'\"", 0, TRUE};
	expected_token[2] = (t_token){WORD, "''", 0, FALSE};
	expected_token[3] = (t_token){WORD, "\"'\"", 0, TRUE};

	int i = -1;
	while (++i < lst_size(lst))
	{
		token = (t_token *)lst->content;
		// ft_printf("EXPEC_CODE:%d CODE:%d\nEXPEC_STR:%s STR:%s\n\n", expected_token[i].code, token->code, expected_token[i].string, token->string);
			if (test_helper(expected_token[i].precedence, expected_token[i].code, expected_token[i].string, expected_token[i].expandable,*token))
				return(EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

char	test_lexer_unseparated_quoted_argv(t_lexer *lexer)
{
	t_token	expected_token[100];
	t_token	*token;
	t_list *lst = *lexer->token_lst;

	// ft_printf("SIZE: %d\n", lst_size(lst));
	if (!lst || lst_size(lst) != 4)
		return (EXIT_FAILURE);

	// "echo \"ola\"'td'\"bem\"";
	expected_token[0] = (t_token){WORD, "echo", 0, TRUE};
	expected_token[1] = (t_token){WORD, "\"ola\"", 0, TRUE};
	expected_token[2] = (t_token){WORD, "'td'", 0, FALSE};
	expected_token[3] = (t_token){WORD, "\"bem\"", 0, TRUE};

	int i = -1;
	while (++i < lst_size(lst))
	{
		token = (t_token *)lst->content;
		// ft_printf("EXPEC_CODE:%d CODE:%d\nEXPEC_STR:%s STR:%s\n\n", expected_token[i].code, token->code, expected_token[i].string, token->string);
			if (test_helper(expected_token[i].precedence, expected_token[i].code, expected_token[i].string, expected_token[i].expandable,*token))
				return(EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

char	test_lexer_separated_quoted_argv(t_lexer *lexer)
{
	t_token	expected_token[100];
	t_token	*token;
	t_list *lst = *lexer->token_lst;

	// ft_printf("SIZE: %d\n", lst_size(lst));
	if (!lst || lst_size(lst) != 4)
		return (EXIT_FAILURE);

	// "echo \"ola\"'td'\"bem\"";
	expected_token[0] = (t_token){WORD, "echo", 0, TRUE};
	expected_token[1] = (t_token){WORD, "\"ola\"", 0, TRUE};
	expected_token[2] = (t_token){WORD, "'td'", 0, FALSE};
	expected_token[3] = (t_token){WORD, "\"bem\"", 0, TRUE};

	int i = -1;
	while (++i < lst_size(lst))
	{
		token = (t_token *)lst->content;
		// ft_printf("EXPEC_CODE:%d CODE:%d\nEXPEC_STR:%s STR:%s\n\n", expected_token[i].code, token->code, expected_token[i].string, token->string);
			if (test_helper(expected_token[i].precedence, expected_token[i].code, expected_token[i].string, expected_token[i].expandable,*token))
				return(EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

char	test_lexer_unclosed_quotes(t_lexer *lexer)
{
	if (lexer->error == TRUE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	free_lexer(void *content)
{
	t_token *token = content;
	if (token->code == WORD)
		free(token->string);
	free(token);
}

int main(void)
{
	t_lexer lexer;
	ft_bzero(&lexer, sizeof(t_lexer));
	char	*tests[100];
	char	(*test_functions[100])(t_lexer *);

	tests[0] = "ls | wc -l";
	tests[1] = "ls|grep";
	tests[2] = "   echo \"Hello world $teste \" | wc -l > outfile.txt && cat outfile.txt && rm -rf outfile.txt";
	tests[3] = "export a=ech && export b=\"o EEEBA\" && $a$b";
	tests[4] = "echo ola\"$USER\"seu\" \"pid$$'$USER''hello'''ola\"oi\"\"\"t";
	tests[5] = "echo \"'\"''\"'\"";
	tests[6] = "echo \"ola\"'td'\"bem\"";
	tests[7] = "echo \"ola\" 'td'\" bem\"";
	tests[10] = "echo \"Hello World";

	test_functions[0] = test_lexer_simple_input;
	test_functions[1] = test_lexer_simple_input_no_spaces;
	test_functions[2] = test_lexer_complex_input;
	test_functions[3] = test_lexer_complex_with_exports;
	test_functions[4] = test_lexer_complex_quoted_with_expandable_and_not_expandable;
	test_functions[5] = test_lexer_complex_quote_sequence;
	test_functions[6] = test_lexer_unseparated_quoted_argv;
	test_functions[7] = test_lexer_separated_quoted_argv;
	test_functions[10] = test_lexer_unclosed_quotes;

	int i = -1;
	while (++i < 8)
	{
	ft_printf(TEST, i + 1, tests[i]);
	ft_lexer(&lexer, tests[i]);
	if (test_functions[i](&lexer))
		ft_printf(FAIL);
	else
		ft_printf(SUCCESS);
	lst_del_all(lexer.token_lst, free_lexer);
	free(lexer.token_lst);
	ft_bzero(&lexer, sizeof(t_lexer));
	}
}