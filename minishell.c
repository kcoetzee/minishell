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
	int		i;
	char	*line;
	char	*format;
	char	**cmd_arr;

	line = NULL;
	ft_putstr(" WHY U NO SEGFAULT! (ノಠ益ಠ)ノ: ");
	while (get_next_line(0, &line) == 1)
	{
		if (line != NULL)
		{
			format = format_input_string(line); // busy
			if (check_semicolon(format) > 0) //checking for a valid semicolon in the string;
			{
				i = -1;
				cmd_arr = ft_split_semi(format);
				while (cmd_arr[++i])
					process_input(&envp, cmd_arr[i]);
				free_strsplit(cmd_arr);
				ft_putstr(" ALL HAIL THE ONE TRUE DEV (ノಠ益ಠ)ノ: ");
			}
			else
			{
				process_input(&envp, format);
				ft_putstr(" WHY U NO SEGFAULT ??? (ノಠ益ಠ)ノ: ");
			}
		}
		free_heap();
	}
}

int		main(int argc, char **argv, char *envp[])
{
	init_heap();
	input_loop(argv, envp);
}