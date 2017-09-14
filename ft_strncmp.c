/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 12:47:53 by lchant            #+#    #+#             */
/*   Updated: 2017/06/02 12:47:58 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *ptr1;
	unsigned char *ptr2;

	ptr1 = (unsigned char*)(s1 - 1);
	ptr2 = (unsigned char*)(s2 - 1);
	while ((--n) + 1 && *(++ptr1) == *(++ptr2) && *ptr1 && *ptr2)
		;
	return (*ptr1 - *ptr2);
}
