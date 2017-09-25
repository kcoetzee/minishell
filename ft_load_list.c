/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlangman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:33:32 by vlangman          #+#    #+#             */
/*   Updated: 2017/09/25 14:55:01 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "main.h"

void	ft_free_list(t_env *list)
{
	t_env	*tempc;
	while(list)
	{
		free(list->str);
		tempc = list->next;
		free(list);
		list = tempc;
	}
	//free(tempc);
}

void	debug_print_env_list(t_env *list)
{
	t_env *it;

	fprintf(stderr, "======================================\n");
	it = list;
	while (it)
	{
		fprintf(stderr, "$%s$\n", it->str);
		it = it->next;
	}
	it = list;
	fprintf(stderr, "======================================\n");
}

t_env	*ft_create_env_list(char **env)
{
	t_env *head;
	t_env *itt;
	int i;
	
	i = 1;
	head = (t_env*)malloc(sizeof(t_env));
	head->str = ft_strdup(env[0]);
	head->next = NULL;
	itt = head;

	while (env[i])
	{
		itt->next = (t_env*)malloc(sizeof(t_env));
		itt = itt->next;
		itt->str = ft_strdup(env[i]);
		itt->next = NULL;
		i++;	
	}
	return (head);
}

/*
t_env	*ft_load_list(char **env)
{
		int		i;
		t_env	*list;
		t_env	*begin;
		
		i = 0;
		list = (t_env*)malloc(sizeof(t_env));
		begin = list;
		while (env[i])
		{
			list->next = (t_env*)malloc(sizeof(t_env));
			list->str = ft_strdup(env[i]);
			list = list->next;
			i++;
		}
		list = NULL;
		return (begin);
}*/
