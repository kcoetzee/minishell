/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:41:17 by lchant            #+#    #+#             */
/*   Updated: 2017/09/24 08:28:07 by kcoetzee         ###   ########.fr       */
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
		/// First check if it's a builtin
		if (try_launch_builtins(list, envp))
		{
			list = list->next;
			break ;
		}
		// Piping
		if (list->terminator[0] == '|')
		{
			debug("PIPING");
			pipe(new_fd);
		}
		pid = fork();

		if (pid == 0) // if child
		{
			// If there is a previous cmd
			if (prev != NULL)
			{
				debug("prev != NULL");
				dup2(old_fd[0], 0);
				close(old_fd[0]);
				close(old_fd[1]);
			}
			// If there is a next command
			if (list->next->file_name != NULL)
			{
				debug("list->next != NULL");
				close(new_fd[0]);
				dup2(new_fd[1], 1);
				close(new_fd[1]);
			}

			fprintf(stderr, "ENTERED LOOP\n");
			launch_program(list, envp);
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
		{
			debug("Child closed");
			fprintf(stderr, "process %d exit with %d\n", pid, WEXITSTATUS(status));
		}
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
