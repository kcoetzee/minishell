/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:08:11 by lchant            #+#    #+#             */
/*   Updated: 2017/09/24 09:02:33 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int		list_len(t_env *list)
{
	int		i;
	t_env	*head;

	i = 1;
	head = list;
	while (list->next)
	{
		list = list->next;
		i++;
	}
	list = head;
	return (i);
}

char	**list_to_arr(t_env *list)
{
	int		len;
	int		i;
	int		j;
	char	**arr;
	t_env	*head;

	i = 0;
	j = -1;
	len = list_len(list);
	arr = (char**)malloc(sizeof(char*) * len);
	while (list->next)
	{
		arr[i] = ft_strdup(list->str);
		i++;
		list = list->next;
	}
	return (arr);
}

/*
** before return in above function do we still need?
** while (arr[++j])
** printf("%d: %s\n", j, arr[j]);
*/

int		pos_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	i++;
	return (i);
}

t_env	*ft_set_env(char *key, char *value, t_env *list)
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
int		run_builtin_setenv(t_command *command, char ***envp)
{
	char	*result;
	t_env	*list;

	list = ft_load_list(*envp);
	list = ft_set_env(command->args->str, command->args->next->str, list);
	*envp = list_to_arr(list);

	return (1);
}
