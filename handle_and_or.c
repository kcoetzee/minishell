/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlangman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 11:56:20 by vlangman          #+#    #+#             */
/*   Updated: 2017/09/28 11:56:21 by vlangman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

char	**ft_split_opps(char *args)
{
	int 	i;
	int 	j;
	char	**ret;

	i = 0;
	j = 0;
	ret = (char**)malloc(sizeof(char*));
	ret[j] = (char*)malloc(sizeof(char));
	while(args[i])
	{
		if (args[i] == '"')
		{
			ret[j] = ft_addchar(ret[j], args[i]);
			while (args[i] != '"' && args[i])
			{
				ret[j] = ft_addchar(ret[j], args[i]);
				i++;
			}
			ret[j] = ft_addchar(ret[j], args[i]);
			i++;
		}
		if (args[i] == '|' && args[i + 1] && args[i + 1] == '|') //found or outside of quotes
		{
			ret[j] = ft_strjoin(ret[j], "||");
			i += 2;
			j++;
			ret[j] = (char*)malloc(sizeof(char));
		}
		else if (args[i] == '&' && args[i + 1] && args[i + 1] == '&')//found and outside quotes
		{
			ret[j] = ft_strjoin(ret[j], "&&");
			i += 2;
			j++;
			ret[j] = (char*)malloc(sizeof(char));
		}
		ret[j] = ft_addchar(ret[j], args[i]);
		i++;
	}
	j++;
	ret[j] = NULL;
	return(ret);
}

t_opps	*create_opps_list(char *args)
{
	int 	i;
	t_opps	*list;
	t_opps	*head;
	char	**cmd_arr;
	char	**temp;

	i = 0;
	cmd_arr = ft_split_opps(args);
	debug("SPLIT INTO CMD_ARR");
	list = (t_opps*)malloc(sizeof(t_opps));
	head = list;
	while(cmd_arr[i])
	{
		fprintf(stderr, "SENDING COMMAND INTO LIST GENORATOR [%s]\n", cmd_arr[i]);
		temp = ft_strsplit(cmd_arr[i], ' ');
		list->cmd = create_command_list(temp);
		list->next = (t_opps*)malloc(sizeof(t_opps));
		i++;
	}
	list->next = NULL;
	return (head);
}

int		and_or_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while(str[i] != '"')
			{
				i++;
				if(!str[i])
					return(0);
			}
			i++;
		}
		if (str[i] == '|' && str[i + 1] && str[i + 1] == '|') //found || outside of quotes
		{
			debug("FOUND OR\n");
			return(1);
		}
		if (str[i] == '&' && str[i + 1] && str[i + 1] == '&')
		{
			debug("FOUND AND\n");
			return(1);
		}
		i++;
	}
	return (0);
}

void		and_or_loop(char ***envp, t_command *list, t_command *prev)
{

}

void		handle_and_or(char ***envp, char *format)
{
	char		**args;
	t_command	*cmd;
	t_command	*prev;
	t_opps		*list;
	

	prev = NULL;
	fprintf(stderr, "ENTER HANDLE OPPS\n");
	list = create_opps_list(format); //split args by || and && into an array then use array to assign list with sub cmd lists of type t_command
	while(list)
	{
		fprintf(stderr, "ONE OF THE COMMAND LISTS\n");
		while(list->cmd)
		{
			fprintf(stderr, "COMMAND: [%s]\n", list->cmd->file_name);
			list->cmd = list->cmd->next;
		}
		list = list->next;
	}
	//and_or_loop(envp, list, prev);
}