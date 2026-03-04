/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:02:37 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/04 18:29:50 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int g_status_shell = 0;

static char	tester_argv_cmp(char **expected, char **argv)
{
	int	i = -1;

	if (ft_split_len(expected) != ft_split_len(argv))
		return (EXIT_FAILURE);
	while (expected[++i])
		if (ft_strcmp(expected[i], argv[i]))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	test_simple_expansion(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(4, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "Hello";
	expected[2] = ft_strcmp(getenv("USER"), "(null)") ? getenv("USER") : "";
	expected[3] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	free(expected);
	return (exit_status);
}

char	test_simple_no_expansion(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(3, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "Hello";
	expected[2] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	free(expected);
	return (exit_status);
}

char	test_simple_quoted_expansion(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(3, sizeof(char *));

	expected[0] = "echo";
	expected[1] = ft_strjoin("Hello ", (ft_strcmp(getenv("USER"), "(null)") ? getenv("USER") : ""));
	expected[2] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	free(expected[1]);
	free(expected);
	return (exit_status);
}

#define TEST_3_VAR_0 (ft_strcmp(getenv("USER"), "(null)") ? getenv("USER") : "")

char	test_complex_expansion(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(3, sizeof(char *));

	// "echo $USER'$NOEXPAND'\"$USER'$USER'\"algumacoisanadahaver$USER";
	expected[0] = "echo";
	expected[1] = ft_strjoin("\'algumacoisanadahaver", TEST_3_VAR_0);
	expected[1] = ft_strjoin_free(TEST_3_VAR_0, expected[1], FALSE, TRUE);
	expected[1] = ft_strjoin_free("'", expected[1], FALSE, TRUE);
	expected[1] = ft_strjoin_free(TEST_3_VAR_0, expected[1], FALSE, TRUE);
	expected[1] = ft_strjoin_free("$NOEXPAND", expected[1], FALSE, TRUE);
	expected[1] = ft_strjoin_free(TEST_3_VAR_0, expected[1], FALSE, TRUE);
	expected[2] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected[1]);
	free(expected);
	return (exit_status);
}


char	test_complex_expansion_with_spaces_in_vars(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(5, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "hello";
	expected[2] = "world";
	expected[3] = ":)";
	expected[4] = NULL;
	

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}

char	test_impossible_expansion_with_dollarsign_inside_var_values(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(2, sizeof(char *));

	expected[0] = "$USER";
	expected[1] = NULL;
	

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}

char	test_madness(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(6, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "hello";
	expected[2] = "doideira infinita";
	expected[3] = "\"big";
	expected[4] = "world\"";
	expected[5] = NULL;	

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}


char	test_quote_inside_quote(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(4, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "'hello world'";
	expected[2] = "\"hello world\"";
	expected[3] = NULL;	

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}

char	test_quoted_empty_var(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(4, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "";
	expected[2] = "hello";
	expected[3] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}

char	test_empty_var(t_msh_ast *node)
{
	char	**argv = expand_argv(node->argv);

	char	**expected = ft_safe_calloc(3, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "hello";
	expected[2] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}

int main(void)
{
	t_mini	mini;
	ft_bzero(&mini, sizeof(mini));
	char	*tests[100] = {NULL};
	char	(*test_functions[100])(t_msh_ast *);

	setenv("a", "ech", 1);
	setenv("b", "o hello", 1);
	setenv("c", " world :)", 1);
	setenv("d", "$", 1);
	setenv("e", "USER", 1);
	setenv("f", " \"big world\"", 1);
	setenv("g", "", 1);
	

	tests[0] = "echo Hello $USER";
	tests[1] = "echo Hello $ASGYUASGUGA";
	tests[2] = "echo \"Hello $USER\"";
	tests[3] = "echo $USER'$NOEXPAND'\"$USER'$USER'\"algumacoisanadahaver$USER";
	tests[4] = "$a$b$c";
	tests[5] = "$d$e";
	tests[6] = "$a$b \"doideira infinita\"$f";
	tests[7] = "echo \"'hello world'\" '\"hello world\"'";
	tests[8] = "echo \"$g\" hello";
	tests[9] = "echo $g hello";
	// tests[4] = "echo ola\"$USER\"seu\" \"pid$$'$USER''hello'''ola\"oi\"\"\"t";
	// tests[5] = "echo \"'\"''\"'\"";
	// tests[6] = "echo \"ola\"'td'\"bem\"";
	// tests[7] = "echo \"ola\" 'td'\" bem\"";
	// tests[8] = "echo oi 'ola' outracoisaai>f1&& echo \"oi\"'ola'\"outracoisaai\" > f2 > f3";
	// tests[9] = "echo & &&& this-should-be-a'&'-cmd-but-this '&&' \"&&\" && &";
	// tests[10] = "echo \"Hello World";

	test_functions[0] = test_simple_expansion;
	test_functions[1] = test_simple_no_expansion;
	test_functions[2] = test_simple_quoted_expansion;
	test_functions[3] = test_complex_expansion;
	test_functions[4] = test_complex_expansion_with_spaces_in_vars;
	test_functions[5] = test_impossible_expansion_with_dollarsign_inside_var_values;
	test_functions[6] = test_madness;
	test_functions[7] = test_quote_inside_quote;
	test_functions[8] = test_quoted_empty_var;
	test_functions[9] = test_empty_var;
	test_functions[10] = NULL;
	test_functions[11] = NULL;
	// test_functions[10] = test_lexer_unclosed_quotes;

	int	test_len = 0;
	while (tests[test_len])
		test_len++;
	int i = -1;
	while (++i < test_len)
	{
	ft_printf(TEST, i + 1, tests[i]);
	mini.input = tests[i];
	process_input_pipeline(&mini);
	if (test_functions[i]((*mini.root)->content))
		ft_printf(FAIL);
	else
		ft_printf(SUCCESS);
	lexer_destroy(&mini.lexer);
	parser_destroy(mini.root);
	ft_bzero(&mini, sizeof(mini));
	}
}
