/*
 * =====================================================================================
 *
 *       Filename:  get_env.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/09/2017 14:53:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "main.h"

char	*ft_get_env(char *key, t_env *list)
{
	int		len;
	char	*str;
	t_env	*head;

	len = ft_strlen(key);
	
	head = list;
	while (list->next)
	{
		if (ft_strncmp(list->str, key, pos_equal(list->str) - 1) == 0)
		{
			str = ft_strsub(list->str, len + 2, ft_strlen(list->str)); 
			return (str);
		}
		list = list->next;
	}
	list = head;
	return (NULL);
}
