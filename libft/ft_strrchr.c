/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 12:45:45 by lchant            #+#    #+#             */
/*   Updated: 2017/06/02 12:46:12 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int n;
	int last;

	i = 0;
	last = 0;
	n = ft_strlen(s);
	while (i < n)
	{
		if (s[i] == c)
			last = i;
		i++;
	}
	if (s[last] == c)
		return ((char *)(s + last));
	if (c == '\0')
		return ((char *)(s + n));
	return (NULL);
}
