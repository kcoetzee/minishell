/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 12:52:03 by lchant            #+#    #+#             */
/*   Updated: 2017/06/02 12:52:19 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int		i;
	unsigned char		d;
	unsigned char		*ptrdst;
	unsigned const char	*ptrsrc;

	i = 0;
	d = (unsigned char)c;
	ptrdst = (unsigned char*)dst;
	ptrsrc = (unsigned const char*)src;
	while (i < n)
	{
		if ((*ptrdst++ = *ptrsrc++) == d)
			return (ptrdst);
		i++;
	}
	return (NULL);
}
