/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:41:17 by lchant            #+#    #+#             */
/*   Updated: 2017/09/25 13:50:57 by kcoetzee         ###   ########.fr       */
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

int	is_opp(char c)
{
	int	i;
	char	*opps;
	char	**arr;

	i = 0;
	opps = ";,>,<,|,&";
	arr = ft_strsplit(opps, ',');
	while (arr[i] && c != arr[i][0])
		i++;
	if (arr[i] &&  c == arr[i][0])
	{
		//free_arr(arr); NEED TO FREE THE ARRAY CREATED BY FT_STRSPLIT
		return(1);
	}
	//free_arr(arr); NEED TO FREE THE ARRAY CREATED BY FT_STRSPLIT
	return(0);
}

char	*remove_tabs(char *line)
{
		int 	i;
		char	*newstr;

		i = 0;
		newstr = ft_strnew(sizeof(char));//using ft_strnew cause malloc fucking sucks
		while(line[i])
		{
			if (line[i] == '\t')
			{
				newstr = ft_addchar(newstr, ' ');
				while(line[i] && line[i] == '\t')
					i++;
			}
			newstr = ft_addchar(newstr, line[i]);
			i++;
		}
		return(newstr);
}

char	*format_opp(char *line)
{
	int		i;
	int		j;
	char	*newstr;	

	i = 0;
	newstr = ft_strnew(sizeof(char));
	while(line[i])
	{
		j = i;
		if (is_opp(line[j]) == 1)
		{
			newstr = ft_addchar(newstr, ' ');
			while (line[j] && is_opp(line[j]) == 1)
			{
				newstr = ft_addchar(newstr, line[j]);
				j++;
			}
			newstr = ft_addchar(newstr, ' ');
			i = j;
		}
		newstr = ft_addchar(newstr, line[i]);
		i++;
	}
	free(line);
	return(newstr);
}

char	*format_input_string(char *line)
{
	int		i;
	int		j;
	char	*trimmed;
	char	*newstr;

	i = 0;
	j = 0;
	trimmed = ft_strnew(sizeof(char));
	trimmed = remove_tabs(line);
	trimmed = ft_strtrim(trimmed);
	trimmed = format_opp(trimmed);
	newstr = ft_strnew(sizeof(char));
	while (trimmed[i])
	{
		while (trimmed[i] != ' ' && trimmed[i])
		{
			newstr = ft_addchar(newstr, trimmed[i]);
			i++;
		}
		if (trimmed[i] == ' ')
		{
			newstr = ft_addchar(newstr, trimmed[i]);
			while(trimmed[i] == ' ' && trimmed[i])
				i++;
		}
	}
	fprintf(stderr, "FORMATTED STRING: %s\n", newstr);
	free(trimmed);
	return(newstr); 
}

void	process_input(char ***envp, char *input)
{
	char **args;
	t_command *head;
	t_command *list;	
	int	new_fd[2];
	int old_fd[2];
	int pid;
	int status;
	t_command *prev;

	
	args = ft_strsplit(input, ' '); 
	list = create_command_list(args); 
	head = list;
	free_strsplit(args);
	prev = NULL;

	while (list)
	{
		/// First check if it's a builtin*
		if (try_launch_builtins(list, envp))
		{
			list = list->next;
			break ;
		}
		//check if opereator terminator
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
			if (list->next != NULL)
			{
				debug("list->next != NULL");
				close(new_fd[0]);
				dup2(new_fd[1], 1);
				close(new_fd[1]);
			}	
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

	if (pid != 0)
	{
		destroy_command_list(head);
	}	

	while ((pid = wait(&status)) != -1)
	{
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
			format = format_input_string(line); // busy
			process_input(&envp, format);
			ft_putstr("【ツ】>: ");
			free(line);
			free(format);
		}
	}
}


int		main(int argc, char **argv, char *envp[])
{
	init_heap();
	input_loop(argv, envp);
}
