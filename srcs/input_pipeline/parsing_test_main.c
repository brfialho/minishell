/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/01 23:58:38 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int g_status_shell = 0;


// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	t_lexer lexer_data;

// 	ft_printf("%s\n", argv[1]);
// 	ft_lexer(&lexer_data, argv[1]);
// 	t_ast **root = parser(&lexer_data);
// 	// if (lexer_data.token_lst)
// 	// 	lst_for_each(*(t_list **)(lexer_data.token_lst), print_node);
// 	lexer_destroy(&lexer_data);
// 	parser_destroy(root);
// }

// void	print_node_2(void *content)
// {
// 	ft_printf("String: %s Expandable:%d\n", ((t_token *)content)->string, ((t_token *)content)->expandable);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	t_mini	mini;

// 	ft_bzero(&mini ,sizeof(t_mini));
// 	set_prompt_signals();
// 	while (TRUE)
// 	{
// 		mini.input = read_prompt_line();
// 		if (mini.input == NULL)
// 			continue;
// 		ft_lexer(&mini.lexer, mini.input);
// 		trim_quoted_tokens11(&mini.lexer);
// 		lst_for_each(*mini.lexer.token_lst, print_node_2);
// 	}
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// }

// static void	destroy_cicle(t_mini *mini);

// int	main(int argc, char **argv, char **env)
// {
// 	t_mini	mini;

// 	ft_bzero(&mini ,sizeof(t_mini));
// 	// mini.input = argv[1];
// 	// if (ft_lexer(&mini.lexer, mini.input))
// 	// 	return (EXIT_FAILURE);
// 	// trim_quoted_tokens(&mini.lexer);
// 	// parser(&mini.root, &mini.lexer);
// 	// destroy_cicle(&mini);
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// }


typedef struct s_exp
{
	int		len;
	char	*start;
	char	*env_key;
	char	*env_value;
}	t_exp;

#define EXPAND_DELIMITER "$'\""
#define EXPAND_SPECIAL "$?"

// char	*set_start_end(char	*s, t_exp *exp_array)
// {
// 	if (ft_str_charcount(EXPAND_SPECIAL, *s))
// 		return (s); // DO SOMETHING

// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (exp_array[i].start)
// 		i++;
// 	exp_array[i].start = s;
// 	while (s[len] && !ft_str_charcount(EXPAND_DELIMITER, s[len]))
// 		len++;
// 	exp_array[i].len = len;
// 	exp_array[i].env_key = ft_substr(s, 0, len);
// 	exp_array[i].env_value = getenv(exp_array[i].env_key);
// 	s += len - 1;
// 	write(1, exp_array[i].start, len);
// 	write(1, "\n", 1);
// 	ft_printf("KEY: %s\nVAL: %s\nLEN:  %d  \nCHAR:  %c\n\n", exp_array[i].env_key, exp_array[i].env_value, len, *exp_array[i].start);
// 	return (s);
// }

// t_exp	*get_exp_array(char *s)
// {
// 	t_bool	expand;
// 	t_exp 	*exp_array;

// 	exp_array = ft_safe_calloc(ft_str_charcount(s, '$') + 1, sizeof(t_exp));
// 	expand = TRUE;
// 	while (*s)
// 	{
// 		// ft_printf("%s :%d\n ", s, expand);
// 		if (*s == '\'' && expand)
// 			expand = FALSE;
// 		else if (*s == '\'')
// 			expand = TRUE;
// 		if (*s == '$' && *(s + 1) && expand)
// 			s = set_start_end(s + 1, exp_array);
// 		s++;
// 	}
// 	return (exp_array);
// }

char	*set_new_expd_var_info(char	*s, t_list **expd_var_lst)
{
	if (ft_str_charcount(EXPAND_SPECIAL, *s))
		return (s); // DO SOMETHING

	t_exp	*content;
	int		len;

	content = ft_safe_calloc(1, sizeof(t_exp));
	len = 0;
	content->start = s;
	while (s[len] && !ft_str_charcount(EXPAND_DELIMITER, s[len]))
		len++;
	content->len = len;
	content->env_key = ft_substr(s, 0, len);
	content->env_value = getenv(content->env_key);
	s += len - 1;
	lst_add_end(expd_var_lst, lst_new_node(content));
	write(1, content->start, len);
	write(1, "\n", 1);
	ft_printf("KEY: %s\nVAL: %s\nLEN:  %d  \nCHAR:  %c\n\n", content->env_key, content->env_value, len, *content->start);
	return (s);
}

t_list	**get_exp_var_lst(char *s)
{
	t_bool	expand;
	t_list 	**expd_var_lst;

	expd_var_lst = ft_safe_calloc(1, sizeof(t_list *));
	expand = TRUE;
	while (*s)
	{
		// ft_printf("%s :%d\n ", s, expand);
		if (*s == '\'' && expand)
			expand = FALSE;
		else if (*s == '\'')
			expand = TRUE;
		if (*s == '$' && *(s + 1) && expand)
			s = set_new_expd_var_info(s + 1, expd_var_lst);
		s++;
	}
	return (expd_var_lst);
}

char	*expand_string(char *s)
{
	t_list	**expd_var_lst;
	// char	*expanded_str;

	if (!ft_str_charcount(s, '$'))
		return (s);
	expd_var_lst = get_exp_var_lst(s);
	lst_del_all(expd_var_lst, NULL);
		

	// expanded_str = ft_safe_calloc(get_expanded_size(string, exp_array) + 1, sizeof(char));
	return (NULL);
}

// "echo \$EXPAND'\$NOEXPAND'\"\$EXPAND\"algumacoisanadahaver\$EXPAND";
int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	// ft_printf("%s\n", argv[1]);
	expand_string(argv[1]);
}

// static void	destroy_cicle(t_mini *mini)
// {
// 	lexer_destroy(&mini->lexer);
// 	parser_destroy(mini->root);
// }