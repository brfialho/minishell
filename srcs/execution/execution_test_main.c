/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:39:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 21:19:06 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>


int g_status_shell = 0;

static void	del_ast_node(void *content)
{
	t_msh_ast	*ast;

	ast = content;
	if (ast->type == NODE_EXEC)
	{
		free(ast->argv);
		lst_del_all(ast->redir, free);
		free(ast->redir);
	}
	free(content);
}

void	init_env(t_env **env, char **envp)
{
	*env = env_from_envp(envp);
}

void	ft_free_ast(t_ast *node)
{
	t_ast	*root;

	root = node;
	ast_del_all(&root, del_ast_node);
}

void	ft_env_clear(t_env **env)
{
	t_env	*current;
	t_env	*temp;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
	*env = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_ast	*node;
	t_msh_ast	*content;
	char		**cmd;

	(void)argc;
	(void)argv;

	init_env(&env, envp);

	// cria argv manual
	cmd = ft_calloc(3, sizeof(char *));
	cmd[0] = ft_strdup("ls");
	cmd[1] = ft_strdup("-l");
	cmd[2] = NULL;

	// cria conteúdo do nó
	content = ft_calloc(1, sizeof(t_msh_ast));
	content->type = NODE_EXEC;
	content->argv = cmd;

	// cria nó AST
	node = ft_calloc(1, sizeof(t_ast));
	node->content = content;
	node->left = NULL;
	node->right = NULL;

	exec_node(node, &env);

	ft_free_ast(node);
	ft_env_clear(&env);

	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;
// 	char	*line;
// 	char	**args;
// 	t_ast	*node;
// 	t_msh_ast	*content;

// 	(void)argc;
// 	(void)argv;

// 	init_env(&env, envp);

// 	while (1)
// 	{
// 		line = readline("exec-test$ ");
// 		if (!line)
// 			break ;
// 		if (*line)
// 			add_history(line);

// 		args = ft_split(line, ' ');

// 		content = ft_calloc(1, sizeof(t_msh_ast));
// 		content->type = NODE_EXEC;
// 		content->argv = args;

// 		node = ft_calloc(1, sizeof(t_ast));
// 		node->content = content;

// 		exec_node(node, &env);

// 		ft_free_ast(node);
// 		free(line);
// 	}
// 	ft_env_clear(&env);
// 	return (0);
// }