/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:39:22 by brfialho          #+#    #+#             */
/*   Updated: 2026/02/24 22:42:59 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>

int g_status_shell = 0;

static void	del_ast_node(void *content)
{
    t_msh_ast	*data;

    if (!content)
        return ;
    data = (t_msh_ast *)content;
    if (data->argv)
        ft_split_free(data->argv);
    if (data->redir)
        lst_del_all(data->redir, free);
    free(data);
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
    t_env	*tmp;

    if (!env || !*env)
        return ;
    while (*env)
    {
        tmp = (*env)->next;
        free((*env)->key);
        free((*env)->value);
        free(*env);
        *env = tmp;
    }
    *env = NULL;
}

static t_ast *create_exec_node(char **argv)
{
    t_ast		*node;
    t_msh_ast	*data;

    node = ft_calloc(1, sizeof(t_ast));
    data = ft_calloc(1, sizeof(t_msh_ast));

    data->type = NODE_EXEC;
    data->argv = argv;
    data->path = NULL;
    data->redir = NULL;
    data->str = NULL;

    node->content = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

static t_ast *create_pipe_node(t_ast *left, t_ast *right)
{
    t_ast		*node;
    t_msh_ast	*data;

    node = ft_calloc(1, sizeof(t_ast));
    data = ft_calloc(1, sizeof(t_msh_ast));

    data->type = NODE_PIPE;

    node->content = data;
    node->left = left;
    node->right = right;

    return (node);
}

int	main(int argc, char **argv, char **envp)
{
    t_env	*env;
    char	*line;
    char	**pipe_split;
    char	**cmd_args;
    t_ast	*node;
    t_ast	*left;
    t_ast	*right;

    (void)argc;
    (void)argv;

    init_env(&env, envp);

    while (1)
    {
        line = readline("exec-test$ ");
        if (!line)
            break ;
        if (*line)
            add_history(line);

        // ---------- PIPE ----------
        if (ft_strchr(line, '|'))
        {
            pipe_split = ft_split(line, '|');

            left = create_exec_node(ft_split(pipe_split[0], ' '));
            right = create_exec_node(ft_split(pipe_split[1], ' '));

            node = create_pipe_node(left, right);
            ft_split_free(pipe_split);
        }
        else
        {
            cmd_args = ft_split(line, ' ');
            node = create_exec_node(cmd_args);
        }

        exec_node(node, &env);
        ft_free_ast(node);
        free(line);
    }

    ft_env_clear(&env);
    return (0);
}