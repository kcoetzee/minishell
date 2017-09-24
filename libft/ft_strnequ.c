/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:43:41 by lchant            #+#    #+#             */
/*   Updated: 2017/05/30 13:43:42 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (n == 0)
	{
		return (1);
	}
	if (s1 == NULL || s2 == NULL)
		return (1);
	if (ft_strncmp(s1, s2, n) == 0)
		return (1);
	else
		return (0);
}
