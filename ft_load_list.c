/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlangman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:33:32 by vlangman          #+#    #+#             */
/*   Updated: 2017/09/28 10:49:17 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	t_env	*head;
	t_env	*itt;
	int		i;

	i = 1;
	head = (t_env*)e_malloc(sizeof(t_env));
	head->str = ft_strdup(env[0]);
	head->next = NULL;
	itt = head;
	while (env[i])
	{
		itt->next = (t_env*)e_malloc(sizeof(t_env));
		itt = itt->next;
		itt->str = ft_strdup(env[i]);
		itt->next = NULL;
		i++;
	}
	return (head);
}
