/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlangman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:33:47 by vlangman          #+#    #+#             */
/*   Updated: 2017/09/13 12:33:48 by vlangman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env		*ft_unset_env(char *key, t_env *list)
{
		int		len;
		t_env	*head;

		head = list;
		len = ft_strlen(key);
		while (list->next != NULL)
		{
			if (ft_strncmp(list->next->str, key, len) == 0)
			{
				list->next = list->next->next;
				free(list->next);
				return(head);
			}
			list = list->next;
		}
		return(head);
}
