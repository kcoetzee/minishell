/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 10:25:43 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/09/28 10:49:18 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			check_opp(char *str)
{
	char	**opps;
	int		i;

	i = 0;
	opps = ft_strsplit(">,<,>>,|,;,&&,||", ',');
	while (opps[i])
	{
		if (ft_strcmp(str, opps[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		arg_list_validation(char **input, t_command *cur_command, int *index)
{
	if (input[*index] == 0)
	{
		cur_command->terminator = ft_strdup("EOF");
		return (0);
	}
	else if (check_opp(input[*index]))
	{
		cur_command->terminator = ft_strdup(input[(*index)++]);
		return (0);
	}
	return (1);
}

t_args	*create_arg_list(char **input, t_command *cur_command, int *index)
{
	t_args	*head;
	t_args	*itt;

	if (arg_list_validation(input, cur_command, index) == 0)
		return (NULL);
	head = (t_args*)e_malloc(sizeof(t_args));
	head->str = ft_strdup(input[(*index)++]);
	head->next = NULL;
	itt = head;
	while (input[*index] && check_opp(input[*index]) != 1)
	{
		itt->next = (t_args*)e_malloc(sizeof(t_args));
		itt = itt->next;
		itt->str = ft_strdup(input[(*index)++]);
		itt->next = NULL;
	}
	if (input[*index] != 0)
		cur_command->terminator = ft_strdup(input[(*index)++]);
	else
		cur_command->terminator = ft_strdup("EOF");
	return (head);
}
