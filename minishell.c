/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:41:17 by lchant            #+#    #+#             */
/*   Updated: 2017/09/18 12:41:18 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** need to take out function but think can include libft.h for
** putchar and putstr and should fix
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	debug(char *str)
{
	ft_putstr("--- ");
	ft_putstr(str);
	ft_putchar('\n');
}

void	ft_putstr(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

/*
** removed comments !!!!!
** TODO
** below was inbetween the first if and args
** char *args[] = {input, 0};
** near end of function but didnt remove for debug
** ft_putstr("The program you are looking for does not exist.\n");
*/

/*void	process_input(char ***envp, char *input)
{
	char **args;

	args = ft_strsplit(input, ' ');
	if (ft_strequ(args[0], "cd"))
		run_builtin_cd(args, *envp);
	else if (ft_strequ(args[0], "echo"))
		run_builtin_echo(args, *envp);
	else if (ft_strequ(args[0], "setenv"))
	{
		run_builtin_setenv(args, envp);
	}
	else if (ft_strequ(args[0], "unsetenv"))
		run_builtin_unsetenv(args, envp);
	else if (ft_strequ(args[0], "env"))
		run_builtin_env(args, *envp);
	else if (ft_strequ(args[0], "exit"))
		run_builtin_exit(args, *envp);
	else
		launch_program(args, *envp);
}*/


void	process_input(char ***envp, char *input)
{
	char **args;
	t_list *list;	
	int	fd[i];
	int pid;
	int status;

	args = ft_strsplit(input, ' ');
	list = create_list(args);

	while (list->next != NULL)
	{
		if (list->terminator[0] == '|')
		{
			pipe(fd);
			execute_command(list, fd, envp); // Run the source command, the writer.
			execute_command(list->next, fd, envp); // The the destination command, the reader.
			close(fd[0]);
			close(fd[1]);
		}
		list = list->next;	
	}
}

void	input_loop(char **argv, char **envp)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	ft_putstr("【ツ】>: ");
	while (get_next_line(0, &line) == 1)
	{
		if (line != NULL)
		{
			if (!ft_strchr(line, '\t'))
			{
				process_input(&envp, line);
				ft_putstr("【ツ】>: ");
				free(line);
			}
		}
	}
}



int		main(int argc, char **argv, char *envp[])
{
	input_loop(argv, envp);
}
