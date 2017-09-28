/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:41:17 by lchant            #+#    #+#             */
/*   Updated: 2017/09/28 09:04:28 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	input_loop(char **argv, char **envp)
{
	char	*line;
	char	*format;
	char	*test;
	int		i;

	i = 0;
	line = NULL;
	ft_putstr("【ツ】>: ");
	while (get_next_line(0, &line) == 1)
	{
		if (line != NULL)
		{
			format = format_input_string(line);
			process_input(&envp, format);
			ft_putstr("【ツ】>: ");
		}
		free_heap();
		free(line);
	}
}

int		main(int argc, char **argv, char *envp[])
{
	init_heap();
	input_loop(argv, envp);
}
