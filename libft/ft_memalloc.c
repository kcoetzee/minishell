/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 11:18:49 by lchant            #+#    #+#             */
/*   Updated: 2017/05/30 11:18:51 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mee_malloc(size_t size)
{
	unsigned char	*len;

	len = (unsigned char*)e_malloc(sizeof(char) * size);
	if (len == NULL)
		return (NULL);
	return (ft_memset(len, 0, size));
}
