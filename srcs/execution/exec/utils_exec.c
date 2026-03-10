/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:42:40 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/10 19:39:22 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
static char *search_in_dirs(char **dirs, char *cmd_name);

static char *search_in_dirs(char **dirs, char *cmd_name)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_path_dirs(t_cmd *cmd, t_env **envp)
{
	char	**dirs;
	char	*path_value;
	char	*result;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (NULL);
	path_value = get_env_value(*envp, "PATH");
	if (ft_strchr(cmd->argv[0], '/'))
    	return (ft_strdup(cmd->argv[0]));
	if (!path_value)
		return (NULL);
	dirs = ft_split(path_value, ':');
	if (!dirs)
		return (NULL);
	result = search_in_dirs(dirs, cmd->argv[0]);
	ft_free_matrix(&dirs);
	return (result);
}

char *get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_free_matrix(char ***matrix)
{
	int	i;

	if (!matrix || !*matrix)
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

void destroy_exec_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->argv)
		ft_split_free(cmd->argv);
	if (cmd->path)
		free(cmd->path);
	if (cmd->redir)
		free_exec_redir_list(cmd->redir);
}
