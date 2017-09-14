/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 08:59:17 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/11 14:25:25 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;
	int k;
	int has_found;

	has_found = 0;
	i = -1;
	if (ft_strlen(little) == 0)
		return ((char*)big);
	while (big[++i] && !has_found)
	{
		if (big[i] == *little)
		{
			j = 0;
			k = i;
			has_found = 1;
			while (*(little + j))
				if (little[j++] != big[k++])
					has_found = 0;
			if (has_found)
				return ((char *)big + i);
		}
	}
	return (NULL);
}
