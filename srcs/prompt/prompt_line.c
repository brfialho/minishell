/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:06:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/05 23:27:07 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// void	colorize_path(char *prompt)
// {
// 	char	*new;
// 	char	*left;
// 	char	*right;
// 	int		i;

// 	i = -1;
// 	new = ft_strdup("");
// 	while (prompt[++i])
// 	{
// 		if (ft_str_charcount("/", prompt[i]))
// 		{
// 			left = ft_substr(prompt + ft_strlen(new), 0, i);
// 			right = ft_strjoin(COLORIZE_AUX_1, prompt + i + 1);
// 			new = ft_strjoin_free(new, ft_strjoin_free(left, right, TRUE, TRUE), TRUE, TRUE);
// 		}
// 	}
// 	ft_memcpy(prompt, new, ft_strlen(new));
// 	free(new);
// }

// oi/mundo

// rest = reset mundo;
// prompt = red + prompt

void	get_prompt(char *prompt)
{
	static char	username[1024] = {0};
	char 		cwd_buffer[1024];
	char		*aux_str;

	if (!*username)
		ft_memcpy(username, getenv("USER"), ft_strlen(getenv("USER")));
	ft_bzero(cwd_buffer, sizeof(cwd_buffer));
	getcwd(cwd_buffer, sizeof(cwd_buffer));
	aux_str = ft_strjoin("/home/", username);
	if (!ft_strncmp(cwd_buffer, aux_str, ft_strlen(aux_str)))
	{
		*prompt = '~';
		ft_memcpy(prompt + 1, cwd_buffer + ft_strlen(aux_str), 1024 - 1 - ft_strlen(aux_str));
	}
	else
		ft_memcpy(prompt, cwd_buffer, 1024);
	free(aux_str);
	aux_str = ft_strjoin(PROMPT_START, prompt);
	ft_memcpy(prompt, aux_str, ft_strlen(aux_str));
	free(aux_str);
	ft_memcpy(prompt + ft_strlen(prompt), PROMPT_END, ft_strlen(PROMPT_END));
	// colorize_path(prompt);
}

char	*read_prompt_line(void)
{
	char		prompt[1024];
	char		*line;

	ft_bzero(prompt, sizeof(prompt));
	get_prompt(prompt);
	line = readline(prompt);
	if (!line)
    	return (NULL);
	if (!*line || ft_str_allinset(line, WHITESPACE))
	{
    	free(line);
    	return (NULL);
	}
	add_history(line);
	return (line);
}
