/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:07:38 by lchant            #+#    #+#             */
/*   Updated: 2017/09/25 15:40:17 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void		free_env(t_env *env)
{
	free(env->str);
	free(env);
}


t_env		*ft_unset_env(char *key, t_env *list)
{
	int		len;
	t_env	*head;
	t_env	*temp;

	head = list;
	len = ft_strlen(key);
	while (list->next != NULL)
	{
		if (list->next->str == NULL)
			return (head);
		if (ft_strncmp(list->next->str, key, len) == 0)
		{
			temp = list->next;
			list->next = list->next->next;
			free_env(temp);
			return (head);
		}
		list = list->next;
	}
	return (head);
}

int	run_builtin_unsetenv(t_command *command, char ***envp)
{
	t_env *list;
	list = ft_create_env_list(*envp);
	list = ft_unset_env(command->args->str, list);
	debug_print_env_list(list);	
	*envp = env_list_to_arr(list);	
	
	ft_free_list(list);	
	return (1);
}
