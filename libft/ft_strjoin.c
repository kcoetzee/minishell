/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:44:04 by lchant            #+#    #+#             */
/*   Updated: 2017/05/30 13:44:05 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*fstr;

	i = -1;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	fstr = (char *)e_malloc((len1 + len2 + 1) * sizeof(char));
	if (fstr == NULL)
		return (NULL);
	while (s1[++i])
		fstr[i] = s1[i];
	while (s2[++j])
	{
		fstr[i] = s2[j];
		i++;
	}
	fstr[i] = '\0';
	return (fstr);
}

char	*e_ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*fstr;

	i = -1;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	fstr = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (fstr == NULL)
		return (NULL);
	while (s1[++i])
		fstr[i] = s1[i];
	while (s2[++j])
	{
		fstr[i] = s2[j];
		i++;
	}
	fstr[i] = '\0';
	return (fstr);
}
