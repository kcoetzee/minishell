/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:33:47 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/11 13:14:52 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char			*str;
	unsigned char	value;

	str = (char *)b;
	value = c;
	while (len--)
	{
		*str++ = value;
	}
	return (b);
}
