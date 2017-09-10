/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:54:41 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/11 13:30:02 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*result;
	char	*ptr;

	len = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (len + 1));
	ptr = result;
	if (result == 0)
		return (NULL);
	while (*s1)
	{
		*result++ = *s1++;
	}
	*result = '\0';
	return (ptr);
}
