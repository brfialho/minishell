/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:05:52 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/23 03:30:19 by brfialho         ###   ########.fr       */
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
		if (!argv[i] || ft_strncmp(expected_argv[i], argv[i], ft_strlen(argv[i])))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);	
}

t_bool	redir_lst___test_parser_cmp(t_list **expected_lst, t_list **lst)
{
	if (!*lst)
		return (EXIT_FAILURE);

	t_list	*exp_lst_ptr;
	t_list	*lst_ptr;
	
	exp_lst_ptr = *expected_lst;
	lst_ptr = *lst;
	while (exp_lst_ptr)
	{
		if (!lst_ptr)
			return (EXIT_FAILURE);
		if (((t_redir *)exp_lst_ptr->content)->type != ((t_redir *)lst_ptr->content)->type
			|| ft_strncmp(((t_redir *)exp_lst_ptr->content)->target, ((t_redir *)lst_ptr->content)->target, ft_strlen(((t_redir *)lst_ptr->content)->target)))
			return (EXIT_FAILURE);
		lst_ptr = lst_ptr->next;
		exp_lst_ptr = exp_lst_ptr->next;
	}
	lst_del_all(expected_lst, NULL);
	return (EXIT_SUCCESS);
}

t_bool	test_parser_cmp(t_msh_ast *expec_content, t_msh_ast *content)
{
	if (!content || expec_content->type != content->type)
		return (EXIT_FAILURE);
	if (expec_content->type != NODE_EXEC && ft_strncmp(expec_content->str, content->str, ft_strlen(content->str)))
		return (EXIT_FAILURE);
	if (expec_content->type == NODE_EXEC && argv___test_parser_cmp(expec_content->argv, content->argv))
		return (EXIT_FAILURE);
	if (expec_content->redir && redir_lst___test_parser_cmp(expec_content->redir, content->redir))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
// ##########################################
//
// test_parser_very_simple_input START
//
// ##########################################

char	**expected_argv_helper___test_parser_very_simple_input(void)
{
	static int i = 0;

	static char *argv_0[] = {"ls", NULL};
	static char *argv_1[] = {"wc", NULL};
	static char **argv[] = {argv_0, argv_1, NULL};
	
	return (argv[i++]);
}

t_msh_ast expected_helper___test_parser_very_simple_input(void)
{
	static t_msh_ast expected_content[100];
	static t_bool init = FALSE;
	static int i = 0;
	
	if (!init)
	{
		expected_content[0] = (t_msh_ast){NODE_PIPE, NULL, NULL, NULL, "|"};
		expected_content[1] = (t_msh_ast){NODE_EXEC, NULL, expected_argv_helper___test_parser_very_simple_input(), NULL, NULL};
		expected_content[2] = (t_msh_ast){NODE_EXEC, NULL, expected_argv_helper___test_parser_very_simple_input(), NULL, NULL};
		init = TRUE;
		return ((t_msh_ast){0, NULL, NULL, NULL, NULL});
	}
	return (expected_content[i++]);
}

t_bool	recursion___test_parser_very_simple_input(t_ast *root)
{
	if (!root)
		return (EXIT_SUCCESS);

	t_msh_ast expected_content = expected_helper___test_parser_very_simple_input();
	
	if(test_parser_cmp(&expected_content, root->content)
		|| recursion___test_parser_very_simple_input(root->left)
		|| recursion___test_parser_very_simple_input(root->right))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_bool	test_parser_very_simple_input(t_ast **root)
{
	if (!root || !*root)
		return (EXIT_FAILURE);

	// TEST DEPTH

	expected_helper___test_parser_very_simple_input();
	return (recursion___test_parser_very_simple_input(*root));
}

// ##########################################
//
// test_parser_simple_input_with_redirs START
//
// ##########################################

t_list **expected_redir_lst_helper___test_parser_simple_input_with_redirs(void)
{
	static t_bool init = FALSE;
	static int i = 0;

	static t_list *lst_0 = NULL;
	static t_redir	lst_0_redir_0 = (t_redir){REDIR_OUT, "f1"};

	static t_list *lst_1 = NULL;
	static t_redir	lst_1_redir_0 = (t_redir){REDIR_OUT, "f2"};
	static t_redir	lst_1_redir_1 = (t_redir){REDIR_OUT, "f3"};

	static t_list **redir_lst_array[3];

	if (!init)
	{
		lst_0 = lst_new_node(&lst_0_redir_0);

		lst_1 = lst_new_node(&lst_1_redir_0);
		lst_add_end(&lst_1, lst_new_node(&lst_1_redir_1));

		redir_lst_array[0] = &lst_0;
		redir_lst_array[1] = &lst_1;
		redir_lst_array[2] = NULL;
		
		init = TRUE;
		return (NULL);
	}
	return (redir_lst_array[i++]);
}

char	**expected_argv_helper___test_parser_simple_input_with_redirs(void)
{
	static int i = 0;

	static char *argv_0[] = {"ls", NULL};
	static char *argv_1[] = {"cat", "f1", NULL};
	static char *argv_2[] = {"wc", NULL};
	static char **argv[] = {argv_0, argv_1, argv_2, NULL};
	
	return (argv[i++]);
}

t_msh_ast expected_helper___test_parser_simple_input_with_redirs(void)
{
	static t_msh_ast expected_content[100];
	static t_bool init = FALSE;
	static int i = 0;
	
	if (!init)
	{
		// "ls > f1 && cat f1 | wc > f2>f3";
		expected_content[0] = (t_msh_ast){NODE_AND, NULL, NULL, NULL, "&&"};
		expected_content[1] = (t_msh_ast){NODE_EXEC, expected_redir_lst_helper___test_parser_simple_input_with_redirs(), expected_argv_helper___test_parser_simple_input_with_redirs(), NULL, NULL};
		expected_content[2] = (t_msh_ast){NODE_PIPE, NULL, NULL, NULL, "|"};
		expected_content[3] = (t_msh_ast){NODE_EXEC, NULL, expected_argv_helper___test_parser_simple_input_with_redirs(), NULL, NULL};
		expected_content[4] = (t_msh_ast){NODE_EXEC, expected_redir_lst_helper___test_parser_simple_input_with_redirs(), expected_argv_helper___test_parser_simple_input_with_redirs(), NULL, NULL};
		init = TRUE;
		return ((t_msh_ast){0, NULL, NULL, NULL, NULL});
	}
	return (expected_content[i++]);
}

t_bool	recursion___test_parser_simple_input_with_redirs(t_ast *root)
{
	if (!root)
		return (EXIT_SUCCESS);

	t_msh_ast expected_content = expected_helper___test_parser_simple_input_with_redirs();
	
	if(test_parser_cmp(&expected_content, root->content)
		|| recursion___test_parser_simple_input_with_redirs(root->left)
		|| recursion___test_parser_simple_input_with_redirs(root->right))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_bool	test_parser_simple_input_with_redirs(t_ast **root)
{
	if (!root || !*root)
		return (EXIT_FAILURE);

	// TEST DEPTH

	expected_redir_lst_helper___test_parser_simple_input_with_redirs();
	expected_helper___test_parser_simple_input_with_redirs();
	return (recursion___test_parser_simple_input_with_redirs(*root));
}

// ##########################################
//
// test_parser_medium_complex_argv_with_redirs START
//
// ##########################################

t_list **expected_redir_lst_helper___test_parser_medium_complex_argv_with_redirs(void)
{
	static t_bool init = FALSE;
	static int i = 0;

	static t_list *lst_0 = NULL;
	static t_redir	lst_0_redir_0 = (t_redir){REDIR_IN, "haesseAquiAindaEhONomeDoRedir"};
	static t_redir	lst_0_redir_1 = (t_redir){REDIR_OUT, "f1"};

	static t_list *lst_1 = NULL;
	static t_redir	lst_1_redir_0 = (t_redir){REDIR_OUT, "f2"};
	static t_redir	lst_1_redir_1 = (t_redir){REDIR_OUT, "out3"};

	static t_list **redir_lst_array[3];

	if (!init)
	{
		lst_0 = lst_new_node(&lst_0_redir_0);
		lst_add_end(&lst_0, lst_new_node(&lst_0_redir_1));

		lst_1 = lst_new_node(&lst_1_redir_0);
		lst_add_end(&lst_1, lst_new_node(&lst_1_redir_1));

		redir_lst_array[0] = &lst_0;
		redir_lst_array[1] = &lst_1;
		redir_lst_array[2] = NULL;
		
		init = TRUE;
		return (NULL);
	}
	return (redir_lst_array[i++]);
}

char	**expected_argv_helper___test_parser_medium_complex_argv_with_redirs(void)
{
	static int i = 0;

	static char *argv_0[] = {"echo", "oi", "ola", "outracoisaai", NULL};
	static char *argv_1[] = {"echo", "oiolaoutracoisaai", NULL};
	static char **argv[] = {argv_0, argv_1, NULL};
	
	return (argv[i++]);
}

t_msh_ast expected_helper___test_parser_medium_complex_argv_with_redirs(void)
{
	static t_msh_ast expected_content[100];
	static t_bool init = FALSE;
	static int i = 0;
	
	if (!init)
	{
		// "echo oi 'ola' outracoisaai>f1&& echo \"oi\"'ola'\"outracoisaai\" > f2 > out3";
		expected_content[0] = (t_msh_ast){NODE_AND, NULL, NULL, NULL, "&&"};
		expected_content[1] = (t_msh_ast){NODE_EXEC, expected_redir_lst_helper___test_parser_medium_complex_argv_with_redirs(), expected_argv_helper___test_parser_medium_complex_argv_with_redirs(), NULL, NULL};
		expected_content[2] = (t_msh_ast){NODE_EXEC, expected_redir_lst_helper___test_parser_medium_complex_argv_with_redirs(), expected_argv_helper___test_parser_medium_complex_argv_with_redirs(), NULL, NULL};
		init = TRUE;
		return ((t_msh_ast){0, NULL, NULL, NULL, NULL});
	}
	return (expected_content[i++]);
}

t_bool	recursion___test_parser_medium_complex_argv_with_redirs(t_ast *root)
{
	if (!root)
		return (EXIT_SUCCESS);

	t_msh_ast expected_content = expected_helper___test_parser_medium_complex_argv_with_redirs();
	
	if(test_parser_cmp(&expected_content, root->content)
		|| recursion___test_parser_medium_complex_argv_with_redirs(root->left)
		|| recursion___test_parser_medium_complex_argv_with_redirs(root->right))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_bool	test_parser_medium_complex_argv_with_redirs(t_ast **root)
{
	if (!root || !*root)
		return (EXIT_FAILURE);

	// TEST DEPTH

	expected_redir_lst_helper___test_parser_medium_complex_argv_with_redirs();
	expected_helper___test_parser_medium_complex_argv_with_redirs();
	return (recursion___test_parser_medium_complex_argv_with_redirs(*root));
}

// ##########################################
//
// test_parser_complex_argv_and_redir_no_expansion START
//
// ##########################################

t_list **expected_redir_lst_helper___test_parser_complex_argv_and_redir_no_expansion(void)
{
	static t_bool init = FALSE;
	static int i = 0;

	static t_list *lst_0 = NULL;
	static t_redir	lst_0_redir_0 = (t_redir){REDIR_OUT, "f1"};
	static t_redir	lst_0_redir_1 = (t_redir){REDIR_OUT, "f2"};

	static t_list **redir_lst_array[2];

	if (!init)
	{
		lst_0 = lst_new_node(&lst_0_redir_0);
		lst_add_end(&lst_0, lst_new_node(&lst_0_redir_1));

		redir_lst_array[0] = &lst_0;
		redir_lst_array[1] = NULL;
		
		init = TRUE;
		return (NULL);
	}
	return (redir_lst_array[i++]);
}

char	**expected_argv_helper___test_parser_complex_argv_and_redir_no_expansion(void)
{
	static int i = 0;

	static char *argv_0[] = {"echo", "ola$USERseu pid$$$USERhello", "olaoit", NULL};
	static char **argv[] = {argv_0, NULL};
	
	return (argv[i++]);
}

t_msh_ast expected_helper___test_parser_complex_argv_and_redir_no_expansion(void)
{
	static t_msh_ast expected_content[100];
	static t_bool init = FALSE;
	static int i = 0;
	
	if (!init)
	{
		// "echo oi 'ola' outracoisaai>f1&& echo \"oi\"'ola'\"outracoisaai\" > f2 > out3";
		expected_content[0] = (t_msh_ast){NODE_EXEC, expected_redir_lst_helper___test_parser_complex_argv_and_redir_no_expansion(), expected_argv_helper___test_parser_complex_argv_and_redir_no_expansion(), NULL, NULL};
		init = TRUE;
		return ((t_msh_ast){0, NULL, NULL, NULL, NULL});
	}
	return (expected_content[i++]);
}

t_bool	recursion___test_parser_complex_argv_and_redir_no_expansion(t_ast *root)
{
	if (!root)
		return (EXIT_SUCCESS);

	t_msh_ast expected_content = expected_helper___test_parser_complex_argv_and_redir_no_expansion();
	
	if(test_parser_cmp(&expected_content, root->content)
		|| recursion___test_parser_complex_argv_and_redir_no_expansion(root->left)
		|| recursion___test_parser_complex_argv_and_redir_no_expansion(root->right))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_bool	test_parser_complex_argv_and_redir_no_expansion(t_ast **root)
{
	if (!root || !*root)
		return (EXIT_FAILURE);

	// TEST DEPTH

	expected_redir_lst_helper___test_parser_complex_argv_and_redir_no_expansion();
	expected_helper___test_parser_complex_argv_and_redir_no_expansion();
	return (recursion___test_parser_complex_argv_and_redir_no_expansion(*root));
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
	tests[1] = "ls > f1 && cat f1 | wc > f2>f3";
	tests[2] = "echo <ha'esseAquiAindaEhONomeDoRedir' oi 'ola' outracoisaai>f1&& echo \"oi\"'ola'\"outracoisaai\" > f2 > out3";
	tests[3] = "echo>f1 ola'$USER'seu\" \"'pid$$''$USER''hello'''>f2 ola\"oi\"\"\"t";

	test_functions[0] = test_parser_very_simple_input;
	test_functions[1] = test_parser_simple_input_with_redirs;
	test_functions[2] = test_parser_medium_complex_argv_with_redirs;
	test_functions[3] = test_parser_complex_argv_and_redir_no_expansion;

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
