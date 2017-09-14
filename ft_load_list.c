/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlangman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:33:32 by vlangman          #+#    #+#             */
/*   Updated: 2017/09/13 12:33:35 by vlangman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "main.h"

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
		return (begin);
}
