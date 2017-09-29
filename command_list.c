/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 10:17:56 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/09/28 10:49:19 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char		**command_to_array(t_command *cmd)
{
	char		**result;
	char		*line;
	t_command	*itt;
	t_args		*args;

	itt = cmd;
	args = cmd->args;
	line = ft_strdup(itt->file_name);
	line = ft_addchar(line, ' ');
	while (args != NULL)
	{
		line = ft_strjoin(line, args->str);
		line = ft_addchar(line, ' ');
		args = args->next;
	}
	result = ft_strsplit(line, ' ');
	return (result);
}

int			ft_arr_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	print_command_list(t_command *command_list)
{
	int	i;
	t_command	*list;
	t_args		*args;

	list = command_list;
	while (list)
	{
		args = list->args;
		debug("--------------------------------------------");
		i = 0;
		printf("FILE_NAME: $%s$\n", list->file_name);
		while(args)
		{
			printf("ARG%d: $%s$\n", i, args->str);
			args = args->next;
			i++;
		}
		printf("TERMINATOR: $%s$\n", list->terminator);
		printf("NEXT: %p\n", list->next);
		list = list->next;
	}	
	debug("--------------------------------------------");
}

t_command	*create_command_list(char **input)
{
	int			i;
	int			len;
	t_command	*head;
	t_command	*itt;

	len = ft_arr_len(input);
	i = 0;
	if (input[i] == 0)
	{
		return (NULL);
	}
	head = (t_command*)e_malloc(sizeof(t_command));
	head->file_name = ft_strdup(input[i++]);
	head->args = create_arg_list(input, head, &i);
	head->next = NULL;
	itt = head;
	while (input[i])
	{
		itt->next = (t_command*)e_malloc(sizeof(t_command));
		itt = itt->next;
		itt->file_name = ft_strdup(input[i++]);
		itt->args = create_arg_list(input, itt, &i);
		itt->next = NULL;
	}
	return (head);
}
