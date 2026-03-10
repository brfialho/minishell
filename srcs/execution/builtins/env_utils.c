/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:21:18 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/10 19:25:33 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_clear(t_env **env)
{
    t_env *tmp;

    while (*env)
    {
        tmp = (*env)->next;
        free((*env)->key);
        free((*env)->value);
        free(*env);
        *env = tmp;
    }
}
static	t_env *env_dup(t_env *env)
{
	t_env *head;
	t_env *node;

	head = NULL;
	while (env)
	{
		node = env_new(env->key, env->value);
		if (!node)
			return (NULL);
		if (!head)
			head = node;
		else
			env_add_back(&head, node);
		env = env->next;
	}
	return (head);
}

static void only_print(t_env *env)
{
	if (!ft_strcmp(env->key, "?"))
		return ;
	if (env->value)
		ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
	else
		ft_printf("declare -x %s\n", env->key);
}

void	env_print_sorted(t_env *env)
{
	t_env	*copy;
	t_env	*current;
	t_env	*min;

	copy = env_dup(env);
	if (!copy)
		return ;
	while (copy)
	{
		current = copy;
		min = copy;
		while (current)
		{
			if (ft_strcmp(current->key, min->key) < 0)
				min = current;
			current = current->next;
		}
		if (ft_strcmp(min->key, "_") != 0)
		{
			only_print(min);
		}
		ft_unset_env(&copy, min->key);
	}
	env_clear(&copy);
}
