/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:58:33 by rafreire          #+#    #+#             */
/*   Updated: 2026/02/19 19:15:55 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*ft_get_envp(t_env *env, char *key)
{
	while (env)
	{
		if (!strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	env_len(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		i;

	envp = safe_calloc(env_len(env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			if (!tmp)
				return (free_envp(envp), NULL);
			envp[i] = ft_strjoin(tmp, env->value);
			free(tmp);
			if (!envp[i])
				return (free_envp(envp), NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
