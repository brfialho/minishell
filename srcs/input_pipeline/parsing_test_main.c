/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/28 00:11:07 by brfialho         ###   ########.fr       */
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
	char	*start;
	char	*end;
	char	*env_key;
	char	*env_value;
}	t_exp;

#define EXPAND_DELIMITER "$'\""
#define EXPAND_SPECIAL "$?"

char	*set_start_end(char	*s, t_exp *exp_array)
{
	int	i;

	i = 0;
	while (exp_array[i].start)
		i++;
	s++;
	if (ft_str_charcount(EXPAND_SPECIAL, *s))
		return (s);
	exp_array[i].start = s;
	int TEST = 0;
	while (*s && !ft_str_charcount(EXPAND_DELIMITER, *s))
		exp_array[i].end = s++, TEST++;
	write(1, exp_array[i].start, TEST);
	write(1, "\n", 1);
	ft_printf("%c %c\n", *exp_array[i].start, *exp_array[i].end);
	return (s - 1);
}

// void	set_key_value(t_exp *exp_array)
// {
// 	int		i;
// 	char	*s;

// 	i = -1;
// 	while (exp_array[++i].start)
// 	{
// 		s = exp_array[i].start;
// 		while (*s != *exp_array[i].end)
// 			*exp_array[i].env_key = *s++;
// 		// ft_printf("%s\n", exp_array);
// 	}
// }

// size_t	get_expanded_size(char *s, t_exp *exp_array)
// {
// 	size_t	len;
// 	int		i;

// 	len = ft_strlen(s);
// 	i = 0;
// 	while (exp_array[i].start)
// 		len += 
// }

t_exp	*get_exp_array(char *s)
{
	t_bool	expand;
	t_exp 	*exp_array;

	exp_array = ft_safe_calloc(ft_str_charcount(s, '$') + 1, sizeof(char));
	expand = TRUE;
	while (*s)
	{
		// ft_printf("%s :%d\n ", s, expand);
		if (*s == '\'' && expand)
			expand = FALSE;
		else if (*s == '\'')
			expand = TRUE;
		if (*s == '$' && expand)
			s = set_start_end(s, exp_array);
		s++;
	}
	// set_key_value(exp_array);
	return (exp_array);
}

char	*expand_string(char *s)
{
	t_exp 	*exp_array;
	// char	*expanded_str;

	if (!ft_str_charcount(s, '$'))
		return (s);
	exp_array = get_exp_array(s);
	exp_array[0].start = NULL;
		

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