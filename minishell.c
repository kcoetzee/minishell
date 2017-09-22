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

int		is_command_terminator(char c)
{
	if (c == '|' || c == '>' || c == ';' || c == '<')
		return (1);
	else 
		return (0);	
}

char	*format_input_string(char *line)
{
	int i;
	int j;
	char *result;
	
	fprintf(stderr, "FORMAT INPUT_STRING\n");
	result = ft_strnew(ft_strlen(line) + 10);
	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
			i++;
	while (line[i])
	{
		if (line[i - 1] && line[i - 1] == ' ' && line[i] == ' ')
		{	
			i++;
		} 
		else if (line[i + 1] && is_command_terminator(line[i + 1]) && line[i] != ' ')
		{
			result[j++] = line[i++];
			result[j++] = ' ';
		}
		else if (line[i + 1] && is_command_terminator(line[i]) && line[i + 1] != ' ')
		{
			result[j++] = line[i++];
			result[j++] = ' ';
		}	
		else
		{	
			result[j] = line[i];
			j++;
			i++;	
		}
	}
	line[i] = '\0';
	fprintf(stderr, "line: $%s$\n", result);	
	return (result);
}

void	process_input(char ***envp, char *input)
{
	char **args;
	t_command *list;	
	int	new_fd[2];
	int old_fd[2];
	int pid;
	int status;
	t_command *prev;

	
	args = ft_strsplit(input, ' ');
	list = create_list(args);
	prev = NULL;


	while (list->next != NULL)
	{
		// Piping
		if (list->terminator[0] == '|')
		{
			pipe(new_fd);
		}
		pid = fork();

		if (pid == 0) // if child
		{
			// If there is a previous cmd
			if (prev != NULL)
			{
				dup2(old_fd[0], 0);
				close(old_fd[0]);
				close(old_fd[1]);
			}
			// If there is a next command
			if (list->next != NULL)
			{
				close(new_fd[0]);
				dup2(new_fd[1], 1);
				close(new_fd[1]);
			}
			launch_program(list, *envp);
		}
		else // if parent
		{	
			if (prev != NULL)
			{
				close(old_fd[0]);
				close(old_fd[1]);
			}
			if (list->next != NULL)
			{
				old_fd[0] = new_fd[0];
				old_fd[1] = new_fd[1];
			}
		}
		prev = list;
		list = list->next;	
	}
	close(old_fd[0]);
	close(old_fd[1]);


		while ((pid = wait(&status)) != -1)
			fprintf(stderr, "process %d exit with %d\n", pid, WEXITSTATUS(status));
}


void	input_loop(char **argv, char **envp)
{
	char	*line;
	char	*format;
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
				format = format_input_string(line);
				process_input(&envp, format);
				ft_putstr("【ツ】>: ");
				free(line);
				free(format);
			}
		}
	}
}



int		main(int argc, char **argv, char *envp[])
{
	input_loop(argv, envp);
}
