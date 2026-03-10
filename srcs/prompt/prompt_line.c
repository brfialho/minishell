/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:06:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/03/10 18:03:32 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	get_prompt(char *prompt);
static void	set_username(char *username);
static void	colorize_path(char *prompt);
static char	*colorize_helper(char *prompt, char c);

char	*read_prompt_line(void)
{
	char		prompt[1024];
	char		*line;

	ft_bzero(prompt, sizeof(prompt));
	get_prompt(prompt);
	g_status_shell = 0;
	rl_event_hook = shell_signal_hook;
	line = readline(prompt);
	rl_event_hook = NULL;
	if (!line)
    	return (NULL);
	if (ft_str_allinset(line, WHITESPACE))
    	return (WHITESPACE);
	add_history(line);
	return (line);
}

static void	get_prompt(char *prompt)
{
	static char	username[1024] = {0};
	char 		cwd_buffer[1024];
	char		*aux_str;

	if (!*username)
		set_username(username);
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
	colorize_path(prompt);
}

static void	set_username(char *username)
{
	char	*user;

	user = getenv("USER");
	if (!user)
	{
		*username = 1;
		return ;
	}
	ft_memcpy(username, user, ft_strlen(user));
}

static void	colorize_path(char *prompt)
{
	char	copy[1024];
	int		i;

	ft_memcpy(copy, prompt, 1024);
	i = -1;
	while (copy[++i])
	{
		if (ft_str_charcount("/$", copy[i]))
			prompt = colorize_helper(prompt, copy[i]);
		else
			*prompt++ = copy[i];
	}
}

static char	*colorize_helper(char *prompt, char c)
{
	char	*color;

	if (c == '/')
		color = COLORIZE_AUX_1;
	if (c == '$')
		color = COLORIZE_AUX_2;
	while (*color)
		*prompt++ = *color++;
	return (prompt);
}






