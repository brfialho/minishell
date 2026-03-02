/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:35 by brfialho          #+#    #+#             */
/*   Updated: 2026/03/02 15:55:24 by brfialho         ###   ########.fr       */
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


typedef struct s_expd
{
	char	*start;
	char	*env_key;
	char	*env_value;
}	t_expd;

#define EXPAND_DELIMITER "$'\""
#define EXPAND_SPECIAL "$?"

char	*set_new_expd_var_info(char	*s, t_list **expd_var_lst)
{
	if (ft_str_charcount(EXPAND_SPECIAL, *s))
		return (s); // DO SOMETHING

	t_expd	*content;
	int		len;

	content = ft_safe_calloc(1, sizeof(t_expd));
	len = 0;
	content->start = s;
	while (s[len] && !ft_str_charcount(EXPAND_DELIMITER, s[len]))
		len++;
	content->env_key = ft_substr(s, 0, len);
	content->env_value = getenv(content->env_key);
	s += len - 1;
	lst_add_end(expd_var_lst, lst_new_node(content));
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

void	del_exp_var(void *content)
{
	t_expd	*exp;

	exp = content;
	free (exp->env_key);
	free(exp);
}

int	get_expanded_len(char *s, t_list *expd_var_lst)
{
	t_list	*lst;
	int		len;

	len = ft_strlen(s);
	lst = expd_var_lst;
	while (lst)
	{
		len += ft_strlen(((t_expd *)lst->content)->env_value);
		lst = lst->next;
	}
	return (len);
}

void	fill_expd_str(char	*old, char *new, t_list *expd_var_lst)
{
	t_list *lst;
	char	*s;

	lst = expd_var_lst;
	while (*old)
	{
		if (lst && old && old + 1 == ((t_expd *)lst->content)->start)
		{
			s = ((t_expd *)lst->content)->env_value;
			while (s && *s)
				*new++ = *s++;
			old += ft_strlen(((t_expd *)lst->content)->env_key);
			new--;
			lst = lst->next;
		}
		else
			*new = *old;
		new++;
		old++;
	}
}

char	*trim_quotes(char *old_str)
{
	char	*new_str;
	char	*new;
	char	*old;
	char	state;

	new_str = ft_safe_calloc(ft_strlen(old_str) + 1, sizeof(char));
	new = new_str;
	old = old_str;
	state = 0;
	while (*old)
	{
		if (state && state == *old)
		{
			state = 0;
			old++;
		}
		else if (state == 0 && (*old == '\'' || *old == '"'))
			state = *old++;
		else 
			*new++ = *old++;
	}
	free (old_str);
	return (new_str);
}

char	*expand_string(char *old_str)
{
	t_list	**expd_var_lst;
	char	*expd_str;

	if (!ft_str_charcount(old_str, '$'))
		return (old_str);
	expd_var_lst = get_exp_var_lst(old_str);
	expd_str = ft_safe_calloc(get_expanded_len(old_str, *expd_var_lst) + 1, sizeof(char));
	fill_expd_str(old_str, expd_str, *expd_var_lst);
	expd_str = trim_quotes(expd_str);

	// ft_printf("\nBEFORE: %s\n", old_str);
	// ft_printf("AFTER : %s\n", expd_str);
	
	lst_del_all(expd_var_lst, del_exp_var);
	free (expd_var_lst);
	return (expd_str);
}

char	**expand_argv(char **old_argv)
{
	char	**argv;
	char	*full_argv;
	int		i;

	i = -1;
	while (old_argv[++i])
		old_argv[i] = expand_string(old_argv[i]);
	i = 0;
	full_argv = ft_strdup(old_argv[i]);
	while (old_argv[++i])
	{
		full_argv = ft_strjoin_free(full_argv, " ", TRUE, FALSE);
		full_argv = ft_strjoin_free(full_argv, old_argv[i], TRUE, FALSE); 
	}
	argv = ft_split(full_argv, ' ');
	free(full_argv);
	ft_split_print(argv);
	return (argv);
}

int main(void)
{
	int size = 2;
	char **argv = ft_calloc(size, sizeof(char *));
	// argv[0] = ft_strdup("echo");
	// argv[1] = ft_strdup("$EXPAND'$NOEXPAND'\"$EXPAND''\"algumacoisanadahaver$EXPAND");
	// argv[2] = ft_strdup("$EXPAND$EXPAND_SPACE$USER");
	// argv[3] = NULL;

	// argv[0] = ft_strdup("$a$b");
	// argv[1] = ft_strdup("$EXPAND'$NOEXPAND'\"$EXPAND''\"algumacoisanadahaver$EXPAND");
	// argv[2] = ft_strdup("$EXPAND$EXPAND_SPACE$USER");
	// argv[3] = NULL;

	argv[0] = ft_strdup("echo");
	argv[1] = NULL;
	expand_argv(argv);
}


// "echo \$EXPAND'\$NOEXPAND'\"\$EXPAND\"algumacoisanadahaver\$EXPAND";
// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return 1;
// 	free (expand_string(argv[1]));
// }
// "echo OI\$USER\"\$VAR_VAZIA''\"'\$NAO_EXPANDE'\$VAR_VAZIA''"
// static void	destroy_cicle(t_mini *mini)
// {
// 	lexer_destroy(&mini->lexer);
// 	parser_destroy(mini->root);
// }