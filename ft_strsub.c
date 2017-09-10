/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 11:51:17 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/11 13:00:11 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char *ft_strnew(int len);

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *new_string;
	size_t i;

	i = 0;
	if (!s)
		return (NULL);
	new_string = ft_strnew(len);
	if (new_string == NULL)
		return (NULL);
	while (i < len)
	{
		*(new_string + i) = *(s + start);
		i++;
		start++;
	}
	return (new_string);
}
