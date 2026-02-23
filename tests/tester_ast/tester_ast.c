/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:05:52 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/22 23:59:18 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int g_status_shell = 0;

t_bool	argv___test_parser_cmp(char **expected_argv, char **argv)
{
	if (!argv)
		return (EXIT_FAILURE);

	int i = -1;
	while (expected_argv[++i])
	{
		if (!argv[i] || ft_strncmp(expected_argv[i], argv[i], ft_strlen(expected_argv[i])))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);	
}

t_bool	test_parser_cmp(t_msh_ast *expec_content, t_msh_ast *content)
{
	if (!content || expec_content->type != content->type)
		return (EXIT_FAILURE);
	if (expec_content->type != NODE_EXEC && ft_strncmp(expec_content->str, content->str, ft_strlen(expec_content->str)))
		return (EXIT_FAILURE);
	if (expec_content->type == NODE_EXEC && argv___test_parser_cmp(expec_content->argv, content->argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	**expected_argv_helper___test_parser_simple_input(void)
{
	static int i = 0;

	static char *argv_0[] = {"ls", NULL};
	static char *argv_1[] = {"wc", NULL};
	static char **argv[] = {argv_0, argv_1, NULL};
	
	return (argv[i++]);
}

// t_list	**expected_redir_helper___test_parser_simple_input(void)
// {
// 	static int init = 0;

// 	static t_list	**redir[3];

// 	static t_list	*redir_lst_0 = NULL;
// 	static t_redir 	redir_0 = 

	
// 	static t_list	*redir_lst_1 = NULL;

// }

t_msh_ast expected_helper___test_parser_simple_input(void)
{
	static t_msh_ast expected_content[100];
	static t_bool init = FALSE;
	static int i = 0;
	
	if (!init)
	{
		expected_content[0] = (t_msh_ast){NODE_PIPE, NULL, NULL, NULL, "|"};
		expected_content[1] = (t_msh_ast){NODE_EXEC, NULL, expected_argv_helper___test_parser_simple_input(), NULL, NULL};
		expected_content[2] = (t_msh_ast){NODE_EXEC, NULL, expected_argv_helper___test_parser_simple_input(), NULL, NULL};
		init = TRUE;
		return ((t_msh_ast){0, NULL, NULL, NULL, NULL});
	}
	return (expected_content[i++]);
}

t_bool	recursion___test_parser_simple_input(t_ast *root)
{
	if (!root)
		return (EXIT_SUCCESS);

	t_msh_ast expected_content = expected_helper___test_parser_simple_input();
	
	if(test_parser_cmp(&expected_content, root->content)
		|| recursion___test_parser_simple_input(root->left)
		|| recursion___test_parser_simple_input(root->right))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_bool	test_parser_simple_input(t_ast **root)
{
	if (!root || !*root)
		return (EXIT_FAILURE);

	// TEST DEPTH

	expected_helper___test_parser_simple_input();
	return (recursion___test_parser_simple_input(*root));
}


int main(void)
{
	t_lexer lexer;
	t_ast	**root;
	ft_bzero(&root, sizeof(t_ast **));
	ft_bzero(&lexer, sizeof(t_lexer));
	char	*tests[100] = {NULL};
	char	(*test_functions[100])(t_ast **);

	tests[0] = "ls | wc";

	test_functions[0] = test_parser_simple_input;

	int test_len = 0;
	while (tests[test_len])
		test_len++;
	int i = -1;
	while (++i < test_len)
	{
	ft_printf(TEST, i + 1, tests[i]);
	ft_lexer(&lexer, tests[i]);
	trim_quoted_tokens(&lexer);
	parser(&root, &lexer);
	if (test_functions[i](root))
		ft_printf(FAIL);
	else
		ft_printf(SUCCESS);
	lexer_destroy(&lexer);
	parser_destroy(root);
	ft_bzero(&lexer, sizeof(t_lexer));
	ft_bzero(&root, sizeof(t_ast **));
	}
}
