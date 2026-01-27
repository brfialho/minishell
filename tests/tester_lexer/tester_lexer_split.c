/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_lexer_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:13:24 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/27 19:30:33 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "tests.h"

int	main(void)
{
	t_lexer lexer;
	ft_bzero(&lexer, sizeof(t_lexer));

	char	**split;
	char	*test1 = "ls | wc -l";
	char	*test2 = "ls|grep";
	char	*test3 = "  echo \"heello world aspas simples=' doideria \" 'aspas denovo\"\"\"' | grep world";

	ft_printf(TEST, test1);
	split = lexer_split(&lexer, test1);
	if (ft_split_len(split) != 4 
		|| ft_strncmp(split[0], "ls", ft_strlen("ls"))
		|| ft_strncmp(split[1], "|", ft_strlen("|"))
		|| ft_strncmp(split[2], "wc", ft_strlen("wc"))
		|| ft_strncmp(split[3], "-l", ft_strlen("-l"))
	)
		ft_printf (FAIL);
	else
		ft_printf (SUCCESS);
	ft_split_free(split);


	ft_printf(TEST, test2);
	split = lexer_split(&lexer, test2);
	if (ft_split_len(split) != 1
		|| ft_strncmp(split[0], "ls|grep", ft_strlen("ls|grep"))
	)
		ft_printf (FAIL);
	else
		ft_printf (SUCCESS);
	ft_split_free(split);


	ft_printf(TEST, test3);
	split = lexer_split(&lexer, test3);
	if (ft_split_len(split) != 6
		|| ft_strncmp(split[0], "echo", ft_strlen("echo"))
		|| ft_strncmp(split[1], "\"heello world aspas simples=' doideria \"", ft_strlen("\"heello world aspas simples=' doideria \""))
		|| ft_strncmp(split[2], "'aspas denovo\"\"\"'", ft_strlen("'aspas denovo\"\"\"'"))
		|| ft_strncmp(split[3], "|", ft_strlen("|"))
		|| ft_strncmp(split[4], "grep", ft_strlen("grep"))
		|| ft_strncmp(split[5], "world", ft_strlen("world"))
	)
		ft_printf (FAIL);
	else
		ft_printf (SUCCESS);
	ft_split_free(split);
}

