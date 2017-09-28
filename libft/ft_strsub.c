/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:11:43 by lchant            #+#    #+#             */
/*   Updated: 2017/06/09 11:11:46 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	sub = ft_strnew(len);
	if (sub == NULL)
		return (NULL);
	s = s + start;
	i = 0;
	while (i < len)
	{
		sub[i] = s[i];
		i++;
	}
	return (sub);
}

char	*e_ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	sub = e_ft_strnew(len);
	if (sub == NULL)
		return (NULL);
	s = s + start;
	i = 0;
	while (i < len)
	{
		sub[i] = s[i];
		i++;
	}
	return (sub);
}