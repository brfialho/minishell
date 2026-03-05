/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:02:37 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/05 20:15:29 by brfialho         ###   ########.fr       */
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

char	test_simple_expansion(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

	char	**expected = ft_safe_calloc(4, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "Hello";
	expected[2] = ft_strcmp(getenv("USER"), "(null)") ? getenv("USER") : "";
	expected[3] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	free(expected);
	return (exit_status);
}

char	test_simple_no_expansion(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

	char	**expected = ft_safe_calloc(3, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "Hello";
	expected[2] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	free(expected);
	return (exit_status);
}

char	test_simple_quoted_expansion(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

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

char	test_complex_expansion(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

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
	ft_printf("%s\n", expected[1]);
	free(expected[1]);
	free(expected);
	return (exit_status);
}


char	test_complex_expansion_with_spaces_in_vars(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

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

char	test_impossible_expansion_with_dollarsign_inside_var_values(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

	char	**expected = ft_safe_calloc(2, sizeof(char *));

	expected[0] = "$USER";
	expected[1] = NULL;
	

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}

char	test_madness(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

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


char	test_quote_inside_quote(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

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

char	test_quoted_empty_var(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

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

char	test_empty_var(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

	char	**expected = ft_safe_calloc(3, sizeof(char *));

	expected[0] = "echo";
	expected[1] = "hello";
	expected[2] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}

char	test_final_boss(t_msh_ast *node, t_env **env)
{
	char	**argv = expand_argv(node->argv, env);

	char	**expected = ft_safe_calloc(4, sizeof(char *));

	// "echo '$X'\"$X '$X'$X\"$X'\"$X\"$X'";
	expected[0] = "echo";
	expected[1] = "$X\"Hello World\" '\"Hello World\"'\"Hello World\"\"Hello";
	expected[2] = "World\"\"$X\"$X";
	expected[3] = NULL;

	char exit_status = tester_argv_cmp(expected, argv);
	// ft_printf("%s\n", expected[1]);
	free(expected);
	return (exit_status);
}

char	test_redir_expansion(t_msh_ast *node, t_env **env)
{
	if (expand_redir(((t_list *)*(node->redir))->content, env))
		return (EXIT_FAILURE);

	char	*expected = ft_strdup("filename");

	char exit_status = ft_strcmp(((t_redir *)((t_list *)*(node->redir))->content)->target, expected);
	free(expected);
	// ft_printf("%s\n", expected[1]);
	return (exit_status);
}

char	test_redir_no_expansion(t_msh_ast *node, t_env **env)
{
	if (expand_redir(((t_list *)*(node->redir))->content, env))
		return (EXIT_FAILURE);

	char	*expected = ft_strdup("$h");

	char exit_status = ft_strcmp(((t_redir *)((t_list *)*(node->redir))->content)->target, expected);
	free(expected);
	// ft_printf("%s\n", expected[1]);
	return (exit_status);
}

char	test_redir_quoted_expansion(t_msh_ast *node, t_env **env)
{
	if (expand_redir(((t_list *)*(node->redir))->content, env))
		return (EXIT_FAILURE);

	char	*expected = ft_strdup("filename");

	char exit_status = ft_strcmp(((t_redir *)((t_list *)*(node->redir))->content)->target, expected);
	free(expected);
	// ft_printf("%s\n", expected[1]);
	return (exit_status);
}

char	test_redir_ambigous(t_msh_ast *node, t_env **env)
{
	return (!expand_redir(((t_list *)*(node->redir))->content, env));
}

char	test_complex_valid_expansion(t_msh_ast *node, t_env **env)
{
	if (expand_redir(((t_list *)*(node->redir))->content, env))
		return (EXIT_FAILURE);

	// "\"Hello World\"";
	// "olha\"$i$i $i'$i'\"'$i'haha";
	char	*expected = ft_strdup("olha\"Hello World\"\"Hello World\" \"Hello World\"'\"Hello World\"'$ihaha");

	char exit_status = ft_strcmp(((t_redir *)((t_list *)*(node->redir))->content)->target, expected);
	free(expected);
	// ft_printf("%s\n", expected[1]);
	return (exit_status);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_mini	mini;
	ft_bzero(&mini, sizeof(mini));
	char	*tests[100] = {NULL};
	char	(*test_functions[100])(t_msh_ast *, t_env **);

	mini.env = env_from_envp(envp);
	ft_set_env(&mini.env, "a", "ech");
	ft_set_env(&mini.env, "b", "o hello");
	ft_set_env(&mini.env, "c", " world :)");
	ft_set_env(&mini.env, "d", "$");
	ft_set_env(&mini.env, "e", "USER");
	ft_set_env(&mini.env, "f", " \"big world\"");
	ft_set_env(&mini.env, "g", "");
	ft_set_env(&mini.env, "X", "\"Hello World\"");
	ft_set_env(&mini.env, "h", "filename");
	ft_set_env(&mini.env, "i", "\"Hello World\"");


	// ARGV EXPANSION
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
	tests[10] = "echo '$X'\"$X '$X'$X\"$X'\"$X\"$X'";

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
	test_functions[10] = test_final_boss;

	// REDIR EXPANSION


	tests[11] = ">$h";
	tests[12] = ">'$h'";
	tests[13] = ">\"$h\"";
	tests[14] = ">$i";
	tests[15] = ">olha\"$i$i $i'$i'\"'$i'haha";

	test_functions[11] = test_redir_expansion;
	test_functions[12] = test_redir_no_expansion;
	test_functions[13] = test_redir_quoted_expansion;
	test_functions[14] = test_redir_ambigous;
	test_functions[15] = test_complex_valid_expansion;

	int	test_len = 0;
	while (tests[test_len])
		test_len++;
	int i = -1;
	while (++i < test_len)
	{
	ft_printf(TEST, i + 1, tests[i]);
	mini.input = tests[i];
	process_input_pipeline(&mini);
	if (test_functions[i]((*mini.root)->content, &mini.env))
		ft_printf(FAIL);
	else
		ft_printf(SUCCESS);
	parser_destroy(mini.root);
	}
}
