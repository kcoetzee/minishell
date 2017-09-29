/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:34:45 by lchant            #+#    #+#             */
/*   Updated: 2017/09/23 16:08:19 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_get_env(char *key, t_env *list)
{
	int		len;
	char	*str;
	t_env	*head;

	len = ft_strlen(key);
	head = list;
	while (list)
	{
		if (ft_strncmp(list->str, key, pos_equal(list->str) - 1) == 0)
		{
			str = ft_strsub(list->str, len + 1, ft_strlen(list->str));
			return (str);
		}
		list = list->next;
	}
	list = head;
	return (NULL);
}
