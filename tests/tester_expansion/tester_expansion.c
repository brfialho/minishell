/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:02:37 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/02 16:57:26 by brfialho         ###   ########.fr       */
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

int main(void)
{
	t_mini	mini;
	ft_bzero(&mini, sizeof(mini));
	char	*tests[100] = {NULL};
	char	(*test_functions[100])(t_msh_ast *);

	tests[0] = "echo Hello $USER";
	// tests[1] = "ls|grep";
	// tests[2] = "   echo \"Hello world $teste \" | wc -l > outfile.txt && cat outfile.txt && rm -rf outfile.txt";
	// tests[3] = "export a=ech && export b=\"o EEEBA\" && $a$b";
	// tests[4] = "echo ola\"$USER\"seu\" \"pid$$'$USER''hello'''ola\"oi\"\"\"t";
	// tests[5] = "echo \"'\"''\"'\"";
	// tests[6] = "echo \"ola\"'td'\"bem\"";
	// tests[7] = "echo \"ola\" 'td'\" bem\"";
	// tests[8] = "echo oi 'ola' outracoisaai>f1&& echo \"oi\"'ola'\"outracoisaai\" > f2 > f3";
	// tests[9] = "echo & &&& this-should-be-a'&'-cmd-but-this '&&' \"&&\" && &";
	// tests[10] = "echo \"Hello World";

	test_functions[0] = test_simple_expansion;
	test_functions[1] = NULL;
	test_functions[2] = NULL;
	test_functions[3] = NULL;
	test_functions[4] = NULL;
	test_functions[5] = NULL;
	test_functions[6] = NULL;
	test_functions[7] = NULL;
	test_functions[8] = NULL;
	test_functions[9] = NULL;
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
