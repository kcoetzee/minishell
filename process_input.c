/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 08:20:34 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/09/28 08:58:53 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	close_old_fd(int *old_fd)
{
	close(old_fd[0]);
	close(old_fd[1]);
}

void	process_input_child(t_command *prev, int *old_fd,
	int *new_fd, t_command *list)
{
	if (prev != NULL)
	{
		dup2(old_fd[0], 0);
		close_old_fd(old_fd);
	}
	if (list->next != NULL)
	{
		close(new_fd[0]);
		dup2(new_fd[1], 1);
		close(new_fd[1]);
	}
}

void	process_input_parent(t_command *prev, int *old_fd,
		int *new_fd, t_command *list)
{
	if (prev != NULL)
		close_old_fd(old_fd);
	if (list->next != NULL)
	{
		old_fd[0] = new_fd[0];
		old_fd[1] = new_fd[1];
	}
}

void	process_input_loop(char ***envp, t_command *list, t_command *prev, int *ret_status)
{
	int			pid1;
	int			new_fd[2];
	int			old_fd[2];
	int 		status;

	while (list)
	{
		if (is_opp_str(list->terminator) > 0)			//found operator that isnt a pipe FOUND
			list = handle_opps(list, envp, old_fd);
		if (try_launch_builtins(list, envp))
		{
			list = list->next;
			break ;
		}
		if (list->terminator[0] == '|')
			pipe(new_fd);
		pid1 = fork();
		if (pid1 == 0)
		{
			debug("RUNNING COMMAND");
			debug(list->file_name);
			process_input_child(prev, old_fd, new_fd, list);
			launch_program(list, envp);
		}
		else
			process_input_parent(prev, old_fd, new_fd, list);
		prev = list;
		list = list->next;
	}
	while (pid1 = wait(&status) != -1)
	{
		fprintf(stderr, "STATUS OF EXIT [%d]\n", status);
		*ret_status = status;
		;
	}
}

void	process_input(char ***envp, char *input)
{
	char		**args;
	t_command	*list;
	t_command	*prev;
	int 		status;

	prev = NULL;
	if (and_or_check(input) == 1)
		handle_and_or(envp, input);
	else
	{
		args = ft_strsplit(input, ' ');
		list = create_command_list(args);
		process_input_loop(envp, list, prev, &status);
	}
}
