/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlangman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:33:42 by vlangman          #+#    #+#             */
/*   Updated: 2017/09/13 12:33:43 by vlangman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	list_len(t_env *list)
{
	int	i;
	t_env	*head;

	i = 1;
	head = list;
	while(list->next)
	{
		list = list->next;
		i++;
	}
	list = head;
	return (i);
}

char	**list_to_arr(t_env *list)
{
	int	len;
	int	i;
	int	j = -1;
	char	**arr;
	t_env	*head;

	i = 0;
	len = list_len(list);
	arr = (char**)malloc(sizeof(char*) * len);
	while(list->next)
	{
		arr[i] = ft_strdup(list->str);
		i++;
		list = list->next;
	}
	//while (arr[++j])
	//	printf("%d: %s\n", j, arr[j]);
	return(arr);
}		

int	pos_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	i++;
	return(i);
}

t_env		*ft_set_env(char *key, char *value, t_env *list)
{
	int		len;
	char	*str;
	t_env	*head;

	str = ft_addchar(key, '=');
	len = ft_strlen(key);
	head = list;
	while (list->next)
	{
		if (ft_strncmp(list->str, str, pos_equal(list->str)) == 0)
		{
			str = ft_strjoin(str, value);
			list->str = ft_strdup(str);
			return (head);
		}
		list = list->next;
	}
	str = ft_strjoin(str, value);
	list->str = ft_strdup(str);
	list->next = (t_env*)malloc(sizeof(t_env));
	return (head);
}
